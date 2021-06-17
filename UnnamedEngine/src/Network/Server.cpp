#include "uepch.h"
#include "Network/Server.h"

#include "Events/NetworkEvent.h"

namespace UE
{
	Server::Server()
	{}

	Server::~Server()
	{}

	void Server::Init(std::string port)
	{
		m_ListeningSocket = Socket::Create();
		m_ListeningConnection = CreateRef<ClientConnection>();
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
			it.second->Disconnect();
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
			std::list<Ref<ServerConnection>>::iterator iter = m_ConnectionManager.GetConnectionsConnecting().begin();
			std::list<Ref<ServerConnection>>::iterator end = m_ConnectionManager.GetConnectionsConnecting().end();
			while (iter != end)
			{
				Ref<ServerConnection> CurrentConnection = *iter;
				//UE_CORE_INFO("Connection request received from {0}", CurrentConnection->GetIPEndpoint().GetAddress());
				
				// Code goes here
				{
					int result = CurrentConnection->Connect();
					if (result == UE_VALUE_SUCCESS)
					{
						ServerConnectedEvent event(CurrentConnection->GetIPEndpoint());
						m_EventCallbackFn(event);
						iter = m_ConnectionManager.GetConnectionsConnecting().erase(iter);
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
			std::list<Ref<ServerConnection>>::iterator iter = m_ConnectionManager.GetConnectionsReceivingPackets().begin();
			std::list<Ref<ServerConnection>>::iterator end = m_ConnectionManager.GetConnectionsReceivingPackets().end();
			while (iter != end)
			{
				Ref<Connection> CurrentConnection = *iter;
				//UE_CORE_INFO("Packet received from {0}", CurrentConnection->GetIPEndpoint().GetAddress());

				// Code goes here
				{
					// Get packet
					Packet ReceivedPacket;
					if (CurrentConnection->GetPacketManager()->RemainingReliableIncomingPackets() > 0)
					{
						ReceivedPacket = *CurrentConnection->GetPacketManager()->GetReliableIncomingPacket();
					}
					else if (CurrentConnection->GetPacketManager()->RemainingUnreliableIncomingPackets() > 0)
					{
						ReceivedPacket = *CurrentConnection->GetPacketManager()->GetUnreliableIncomingPacket();
					}
					else
					{
						// Todo: this should not happen, but MAYBE can cause an error on the future
						// The possible future error will have something related to a blank packet being received from
						// the event bellow.
					}

					// Send event containing packet
					ServerPacketEvent event(CurrentConnection->GetIPEndpoint(), ReceivedPacket);
					m_EventCallbackFn(event);
				}

				iter = m_ConnectionManager.GetConnectionsReceivingPackets().erase(iter);
			}
		}

		// Check for received errors
		{
			std::list<Ref<ServerConnection>>::iterator iter = m_ConnectionManager.GetConnectionsReceivingErrors().begin();
			std::list<Ref<ServerConnection>>::iterator end = m_ConnectionManager.GetConnectionsReceivingErrors().end();
			while (iter != end)
			{
				Ref<Connection> CurrentConnection = *iter;
				UE_CORE_ERROR("Error at connection {0}", CurrentConnection->GetIPEndpoint().GetAddress());

				{

				}

				iter = m_ConnectionManager.GetConnectionsReceivingErrors().erase(iter);
			}
		}

		// Todo: Create packets with messages (just call OnUpdate for each connection)
		{
			std::unordered_map<IPEndpoint, Ref<ServerConnection>>::iterator iter = m_ConnectionManager.GetConnections().begin();
			std::unordered_map<IPEndpoint, Ref<ServerConnection>>::iterator end = m_ConnectionManager.GetConnections().end();
			while (iter != end)
			{
				Ref<Connection> CurrentConnection = iter->second;
				
				{
					if (CurrentConnection->IsConnected())
					{
						// Send heartbeat message
						CurrentConnection->SendHeartbeat();

						// Create packets with messages
						CurrentConnection->OnUpdate();
					}
				}

				iter++;
			}
		}


		// Send packets
		{
			std::unordered_map<IPEndpoint, Ref<ServerConnection>>::iterator iter = m_ConnectionManager.GetConnections().begin();
			std::unordered_map<IPEndpoint, Ref<ServerConnection>>::iterator end = m_ConnectionManager.GetConnections().end();
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
						IPEndpoint Destination = CurrentConnection->GetIPEndpoint();
						Destination.SetPort("27016");
						m_ListeningSocket->SendTo(Destination, *CurrentConnection->GetPacketManager()->GetUnreliableOutgoingPacket());
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