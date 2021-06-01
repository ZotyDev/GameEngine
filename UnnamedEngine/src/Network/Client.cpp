#include "uepch.h"
#include "Network/Client.h"

#include "Math/Random/Salt.h"

#include "Events/NetworkEvent.h"

namespace UE
{
	Client::Client()
	{
		m_Socket = Socket::Create();
		m_Connection = CreateRef<ClientConnection>();
	}

	Client::~Client()
	{}

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
			if (m_Connection->Connect() == UE_VALUE_SUCCESS)
			{
				ClientConnectedEvent event(m_Connection->GetIPEndpoint());
				m_EventCallbackFn(event);
				m_AttemptingConnection = false;
			}
		}
		else // UpdateCode
		{
			// Send event containing received packet
			if (m_Connection->GetPacketManager()->RemainingReliableIncomingPackets() > 0)
			{
				Packet ReceivedPacket = *m_Connection->GetPacketManager()->GetReliableIncomingPacket();

				ClientPacketEvent event(m_Connection->GetIPEndpoint(), ReceivedPacket);
				m_EventCallbackFn(event);
			}
		}

		m_Connection->OnUpdate();

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