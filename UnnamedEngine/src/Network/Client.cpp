#include "uepch.h"
#include "Network/Client.h"

namespace UE
{
	Client::Client()
	{
	}

	Client::~Client()
	{
	}

	void Client::Init()
	{
		m_Socket = Socket::Create();
		m_Connection = CreateRef<Connection>();
		int result = m_Socket->Init();
		if (result == UE_VALUE_ERROR)
		{
			UE_CORE_ERROR("Client Init() failed: could not initialize socket");
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
		if (m_AttemptingConnection)
		{
			m_Connection->ClientConnect();
		}

		if (m_Connection->GetOutgoingPacketQueueSize() > 0)
		{
			Packet SentPacket = *m_Connection->GetOutgoingPacket();
			IPEndpoint Destination = *m_Connection->GetIPEndpoint();
			m_Socket->SendTo(Destination, SentPacket);
		}
		//UE_CORE_INFO("Don't go bananas yet");
	}

	int Client::Connect(IPEndpoint destination)
	{
		m_Connection->GetIPEndpoint()->SetIp(destination.GetIp());
		m_Connection->GetIPEndpoint()->SetPort(destination.GetPort());

		m_AttemptingConnection = true;

		return 0;
	}
}