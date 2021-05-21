#include "uepch.h"
#include "Network/Server.h"

namespace UE
{
	Server::Server()
	{
		m_ConnectionManager = ConnectionManager::Create();
	}

	Server::~Server()
	{
	}

	void Server::Init(std::string port)
	{
		m_ListeningSocket = Socket::Create();
		m_ListeningConnection = CreateRef<Connection>();
		int result = m_ListeningSocket->Init();
		if (result == UE_VALUE_ERROR)
		{
			UE_CORE_ERROR("UnnamedEngine Server Init() failed: could not initialize socket");
			return;
		}

		m_ListeningConnection->GetIPEndpoint()->SetIp("127.0.0.1");
		m_ListeningConnection->GetIPEndpoint()->SetPort(port);
		result = m_ListeningSocket->Bind(*m_ListeningConnection->GetIPEndpoint().get());
		if (result == UE_VALUE_ERROR)
		{
			UE_CORE_ERROR("UnanmedEngine Server Init() failed: could not bind socket");
			return;
		}

		result = m_ListeningSocket->Block(false);
		if (result == UE_VALUE_ERROR)
		{
			UE_CORE_ERROR("UnnamedEngine Server Init() failed: could not set socket to non-blocking mode");
			return;
		}

		m_ConnectionManager->Init(m_ListeningSocket);
	}

	void Server::Shutdown()
	{
		// Disconnect all clients
		for (auto& it : m_ConnectionManager->GetConnections())
		{
			it.second->ServerDisconnect();
		}

		// Shutdown the listening socket
		m_ListeningSocket->Shutdown();
	}

	void Server::OnUpdate()
	{
		// Poll for updates
		m_ConnectionManager->Poll();

		// Check for connections
		{
			std::list<Ref<Connection>>::iterator iter = m_ConnectionManager->GetConnectionsStarting().begin();
			std::list<Ref<Connection>>::iterator end = m_ConnectionManager->GetConnectionsStarting().end();
			while (iter != end)
			{
				Ref<Connection> CurrentConnection = *iter;
				UE_CORE_INFO("Connection request received from {0}", CurrentConnection->GetIPEndpoint()->GetAddress());

				/*Packet ReceivedPacket = *CurrentConnection->GetIncomingPacket();

				uint64_t ClientSalt = 0;
				ReceivedPacket >> ClientSalt;
				UE_CORE_INFO("Client salt is: {0}", ClientSalt);*/

				iter = m_ConnectionManager->GetConnectionsStarting().erase(iter);
			}
		}

		// Check for received packets
		{
			std::list<Ref<Connection>>::iterator iter = m_ConnectionManager->GetConnectionsReceivingPackets().begin();
			std::list<Ref<Connection>>::iterator end = m_ConnectionManager->GetConnectionsReceivingPackets().end();
			while (iter != end)
			{
				Ref<Connection> CurrentConnection = *iter;
				UE_CORE_INFO("Packet received from {0}", CurrentConnection->GetIPEndpoint()->GetAddress());

				iter = m_ConnectionManager->GetConnectionsReceivingPackets().erase(iter);
			}
		}

		// Check for received errors
		{
			std::list<Ref<Connection>>::iterator iter = m_ConnectionManager->GetConnectionsReceivingErrors().begin();
			std::list<Ref<Connection>>::iterator end = m_ConnectionManager->GetConnectionsReceivingErrors().end();
			while (iter != end)
			{
				Ref<Connection> CurrentConnection = *iter;
				UE_CORE_ERROR("Error at connection {0}", CurrentConnection->GetIPEndpoint()->GetAddress());

				iter = m_ConnectionManager->GetConnectionsReceivingErrors().erase(iter);
			}
		}
	}
}