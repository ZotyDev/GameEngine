#include "uepch.h"
#include "Network/Server.h"

namespace UE
{
	Server::Server()
	{

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

		IPEndpoint ServerAddress;
		ServerAddress.SetIp("0.0.0.0");
		ServerAddress.SetPort(port);

		m_ListeningConnection->SetIPEndpoint(ServerAddress);
		result = m_ListeningSocket->Bind(m_ListeningConnection->GetIPEndpoint());
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

		m_ConnectionManager.Init(m_ListeningSocket);
	}

	void Server::Shutdown()
	{
		// Disconnect all clients
		for (auto& it : m_ConnectionManager.GetConnections())
		{
			it.second->ServerDisconnect();
		}

		// Shutdown the listening socket
		m_ListeningSocket->Shutdown();
	}

	void Server::OnUpdate()
	{
		// Poll for updates
		m_ConnectionManager.Poll();

		// Check for connections
		{
			std::list<Ref<Connection>>::iterator iter = m_ConnectionManager.GetConnectionsStarting().begin();
			std::list<Ref<Connection>>::iterator end = m_ConnectionManager.GetConnectionsStarting().end();
			while (iter != end)
			{
				Ref<Connection> CurrentConnection = *iter;
				//UE_CORE_INFO("Connection request received from {0}", CurrentConnection->GetIPEndpoint().GetAddress());
				
				{
					int result = CurrentConnection->ServerConnect();
					if (result == UE_VALUE_SUCCESS)
					{
						iter = m_ConnectionManager.GetConnectionsStarting().erase(iter);
					}
					else
					{
						iter++;
					}
				}
			}
		}

		// Check for received packets
		{
			std::list<Ref<Connection>>::iterator iter = m_ConnectionManager.GetConnectionsReceivingPackets().begin();
			std::list<Ref<Connection>>::iterator end = m_ConnectionManager.GetConnectionsReceivingPackets().end();
			while (iter != end)
			{
				Ref<Connection> CurrentConnection = *iter;
				UE_CORE_INFO("Packet received from {0}", CurrentConnection->GetIPEndpoint().GetAddress());

				{

				}

				iter = m_ConnectionManager.GetConnectionsReceivingPackets().erase(iter);
			}
		}

		// Check for received errors
		{
			std::list<Ref<Connection>>::iterator iter = m_ConnectionManager.GetConnectionsReceivingErrors().begin();
			std::list<Ref<Connection>>::iterator end = m_ConnectionManager.GetConnectionsReceivingErrors().end();
			while (iter != end)
			{
				Ref<Connection> CurrentConnection = *iter;
				UE_CORE_ERROR("Error at connection {0}", CurrentConnection->GetIPEndpoint().GetAddress());

				{

				}

				iter = m_ConnectionManager.GetConnectionsReceivingErrors().erase(iter);
			}
		}

		// Send packets
		{
			std::unordered_map<IPEndpoint, Ref<Connection>>::iterator iter = m_ConnectionManager.GetConnections().begin();
			std::unordered_map<IPEndpoint, Ref<Connection>>::iterator end = m_ConnectionManager.GetConnections().end();
			while (iter != end)
			{
				Ref<Connection> CurrentConnection = iter->second;

				{
					// Send reliable packets
					if (CurrentConnection->GetPacketManager()->RemainingReliableOutgoingPackets() > 0)
					{
						IPEndpoint Destination = CurrentConnection->GetIPEndpoint();
						Destination.SetPort("27016");
						m_ListeningSocket->SendTo(Destination, *CurrentConnection->GetPacketManager()->GetReliableOutgoingPacket());
					}

					// Send unreliable packets
					if (CurrentConnection->GetPacketManager()->RemainingUnreliableOutgoingPackets() > 0)
					{
						m_ListeningSocket->SendTo(CurrentConnection->GetIPEndpoint(), *CurrentConnection->GetPacketManager()->GetUnreliableOutgoingPacket());
					}
				}

				iter++;
			}
		}
	}

	int Server::SendMessage(Ref<Message> message)
	{
		return m_ListeningConnection->SendMessage(message);
	}
}