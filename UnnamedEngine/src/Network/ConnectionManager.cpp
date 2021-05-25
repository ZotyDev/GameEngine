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

		if (m_ListeningSocket->IsReceivingPackets())
		{
			// Receive packet and sender identification
			IPEndpoint SenderIPEndpoint;
			Packet ReceivedPacket;
			int result = m_ListeningSocket->RecvFrom(SenderIPEndpoint, ReceivedPacket);
			if (result == UE_VALUE_ERROR)
			{
				UE_CORE_ERROR("ConnectionManager Poll() failed: Socket RecvFrom() failed");
				return -1;
			}

			// Check if client is not on connection list
			if (m_Connections.find(SenderIPEndpoint) == m_Connections.end())
			{
				// ConnectionRequest
				if (ReceivedPacket.GetPacketType() == Packet::PacketType::ConnectionRequest)
				{
					// Start connection with client
					Ref<Connection> NewConnection = CreateRef<Connection>();
					NewConnection->SetIPEndpoint(SenderIPEndpoint);
					NewConnection->GetPacketManager()->Receive(CreateRef<Packet>(ReceivedPacket));
					m_Connections.insert({ SenderIPEndpoint, NewConnection });
					m_ConnectionsStarting.push_back(NewConnection);

					return 0;
				}
			}
			else // Client is on cconnection list
			{
				Ref<Connection> CurrentConnection = m_Connections.at(SenderIPEndpoint);

				// Check if client is not connected
				if (!CurrentConnection->IsConnected())
				{
					CurrentConnection->GetPacketManager()->Receive(CreateRef<Packet>(ReceivedPacket));

					return 0;
				}

				// MessagePacket
				if (ReceivedPacket.GetPacketType() == Packet::PacketType::MessagePacket)
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
		}

		return 0;
	}
}