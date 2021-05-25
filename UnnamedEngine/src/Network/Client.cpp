#include "uepch.h"
#include "Network/Client.h"

#include "Math/Random/Salt.h"

namespace UE
{
	Client::Client()
	{
		m_Socket = Socket::Create();
		m_Connection = CreateRef<Connection>();
	}

	Client::~Client()
	{
	}

	void Client::Init()
	{
		int result = m_Socket->Init();
		if (result == UE_VALUE_ERROR)
		{
			UE_CORE_ERROR("Client Init() failed: could not initialize socket");
			return;
		}

		IPEndpoint MyAddress;
		MyAddress.SetIp("0.0.0.0");
		MyAddress.SetPort("27016");
		result = m_Socket->Bind(MyAddress);
		if (result == UE_VALUE_ERROR)
		{
			UE_CORE_ERROR("Client Init() failed: coult not bind socket");
			return;
		}

		result = m_Socket->Block(false);
		if (result == UE_VALUE_ERROR)
		{
			UE_CORE_ERROR("Client Init() failed: could not set socket to non-blocking mode");
			return;
		}
	}

	void Client::Shutdown()
	{
		m_Socket->Shutdown();
	}

	void Client::OnUpdate()
	{
		// Connection code
		if (m_AttemptingConnection)
		{
			if (m_Connection->ClientConnect() == UE_VALUE_SUCCESS)
			{
				m_AttemptingConnection = false;
			}
		}
		else // UpdateCode
		{

		}


		// Construct reliable packet
		if (m_Connection->GetMessageManager()->GetReliableOutgoingMessageCount() > 0)
		{
			Packet ReliableOutgoingPacket(Packet::PacketType::MessagePacket);
			ReliableOutgoingPacket.SetPacketReliability(true);
			ReliableOutgoingPacket << *m_Connection->GetMessageManager()->GetReliableOutgoingMessage();

			m_Connection->GetPacketManager()->Send(CreateRef<Packet>(ReliableOutgoingPacket));
		}

		// Construct unreliable packet
		if (m_Connection->GetMessageManager()->GetUnreliableOutgoingMessageCount() > 0)
		{
			Packet UnreliableOutgoingPacket(Packet::PacketType::MessagePacket);
			UnreliableOutgoingPacket.SetPacketReliability(false);
			UnreliableOutgoingPacket << *m_Connection->GetMessageManager()->GetUnreliableOutgoingMessage();

			m_Connection->GetPacketManager()->Send(CreateRef<Packet>(UnreliableOutgoingPacket));
		}

		// Send reliable packets
		if (m_Connection->GetPacketManager()->RemainingReliableOutgoingPackets() > 0)
		{
			m_Socket->SendTo(m_Connection->GetIPEndpoint(), *m_Connection->GetPacketManager()->GetReliableOutgoingPacket());
		}

		// Send unreliable packets
		if (m_Connection->GetPacketManager()->RemainingUnreliableOutgoingPackets() > 0)
		{
			m_Socket->SendTo(m_Connection->GetIPEndpoint(), *m_Connection->GetPacketManager()->GetUnreliableOutgoingPacket());
		}
		
		// Receive packets
		IPEndpoint ServerAddress;
		Packet ReceivedPacket;

		m_Socket->Poll();

		if (m_Socket->IsReceivingPackets())
		{
			int result = m_Socket->RecvFrom(ServerAddress, ReceivedPacket);
			if (result == UE_VALUE_ERROR)
			{
				UE_CORE_ERROR("Client OnUpdate() failed: Socket RecvFrom() failed");
				return;
			}
			else if (result == -2)
			{
				return;
			}

			m_Connection->GetPacketManager()->Receive(CreateRef<Packet>(ReceivedPacket));
		}
	}

	int Client::Connect(IPEndpoint destination)
	{
		m_Connection->SetIPEndpoint(destination);
		m_AttemptingConnection = true;

		return 0;
	}

	int Client::SendMessage(Ref<Message> message)
	{
		return m_Connection->SendMessage(message);
	}
}