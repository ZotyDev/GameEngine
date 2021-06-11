#include "uepch.h"
#include "Network/ConnectionManager.h"

namespace UE
{
	ConnectionManager::ConnectionManager()
	{
	}

	ConnectionManager::~ConnectionManager()
	{
	}

	int ConnectionManager::Init(Ref<Socket> listeningSocket)
	{
		m_ListeningSocket = listeningSocket;

		return 0;
	}

	int ConnectionManager::Poll()
	{
		int result = m_ListeningSocket->Poll();
		if (result == UE_VALUE_ERROR)
		{
			UE_CORE_ERROR("ConnectionManager Poll() failed: Socket Poll() failed");
			return -1;
		}
		else if (result == 0)
		{
			return 0;
		}

		// todo: do checksum to prevent packets from crashing server

		if (m_ListeningSocket->IsReceivingPackets())
		{
			// Receive packet and IPEndpoint
			Packet ReceivedPacket;
			IPEndpoint ReceivedIPEndpoint;
			int result = m_ListeningSocket->RecvFrom(ReceivedIPEndpoint, ReceivedPacket);
			if (result == UE_VALUE_ERROR)
			{
				UE_CORE_ERROR("ConnectionManager Poll() failed: Socket RecvFrom() failed");
				return -1;
			}

			// Checksum the packet header
			// 1   - protocol
			// 2   - reliability
			// 3~4 - packet type
			if (!ReceivedPacket.IsGreaterEqualToChecksum(4))
			{
				UE_CORE_ERROR("Bad packet received from {0} : Missing packet header", ReceivedIPEndpoint.GetAddress());
				// Todo: block connection for 5 min if it becomes constant
				return 0;
			}

			// Check packet protocol
			if (ReceivedPacket.GetPacketProtocol() != PacketProtocol::UEUDP)
			{
				UE_CORE_ERROR("Bad packet received from {0} : Unknown protocol", ReceivedIPEndpoint.GetAddress());
				// Todo: block connection for 5 min if it becomes constant
				return 0;
			}

			PacketType ReceivedPacketType = ReceivedPacket.GetPacketType();

			// Todo: if the connection is not on m_Connections try to check ClientServerSalt of the packet
			// If the ClientServerSalt exist delete the old connection on m_Connections and insert a new one using new IPEndpoint
			// If the ClientServerSalt doesn't exist just add a new one

			// Use IPEndpoint to check if client is not on the list
			if (m_Connections.find(ReceivedIPEndpoint) == m_Connections.end())
			{
				if (ReceivedPacketType == PacketType::ConnectionRequestPacket)
				{
					// Start connection with client
					Ref<ServerConnection> NewConnection = CreateRef<ServerConnection>();
					NewConnection->SetIPEndpoint(ReceivedIPEndpoint);
					
					// Receive packet
					NewConnection->GetPacketManager()->Receive(CreateRef<Packet>(ReceivedPacket));

					// Add new connection to connections and connections connecting
					m_Connections.insert({ ReceivedIPEndpoint, NewConnection });
					m_ConnectionsConnecting.push_back(m_Connections.at(ReceivedIPEndpoint));

					return 0;
				}
				else
				{
					UE_CORE_ERROR("Bad packet received from {0} : Expected ConnectionRequestPacket, received other", ReceivedPacketType);
					// Todo: block connection for 5 min if it becomes constant
					return 0;
				}
			}

			// Get current connection
			Ref<ServerConnection> CurrentConnection = m_Connections.at(ReceivedIPEndpoint);

			// Connection Type Packet
			if (ReceivedPacketType >= PacketType::ConnectionFirstPacket && ReceivedPacketType <= PacketType::ConnectionLastPacket)
			{
				// Check if client is connecting
				if (!CurrentConnection->IsConnected())
				{
					// Execute connection code
					CurrentConnection->GetPacketManager()->Receive(CreateRef<Packet>(ReceivedPacket));
					m_ConnectionsConnecting.push_back(m_Connections.at(ReceivedIPEndpoint));
				}
				else
				{
					UE_CORE_ERROR("Bad packet received from {0} : Expected Connection Type, received other", ReceivedPacketType);
					// Todo: block connection for 5 min if it becomes constant
				}

				return 0;
			}

			// Message Packet
			if (ReceivedPacket.GetPacketType() == PacketType::MessagePacket)
			{
				CurrentConnection->GetPacketManager()->Receive(CreateRef<Packet>(ReceivedPacket));
				m_ConnectionsReceivingPackets.push_back(CurrentConnection);

				return 0;
			}

			// Unknown PacketType
			CurrentConnection->GetPacketManager()->Receive(CreateRef<Packet>(ReceivedPacket));
			m_ConnectionsReceivingErrors.push_back(CurrentConnection);

			return 0;
		}

		return 0;
	}
}