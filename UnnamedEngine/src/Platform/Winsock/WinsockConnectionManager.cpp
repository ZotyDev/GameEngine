#include "uepch.h"
#include "Platform/Winsock/WinsockConnectionManager.h"

namespace UE
{
	WinsockConnectionManager::WinsockConnectionManager()
	{
	}

	WinsockConnectionManager::~WinsockConnectionManager()
	{
	}

	int WinsockConnectionManager::Init(Ref<Socket> listeningSocket)
	{
		m_ListeningSocket = listeningSocket;

		m_ListeningSocketFD[0].fd = *(SOCKET*)listeningSocket->GetNativeSocket();
		m_ListeningSocketFD[0].events = POLLRDNORM;
		m_ListeningSocketFD[0].revents = 0;

		return 0;
	}

	int WinsockConnectionManager::Poll()
	{
		//m_ConnectionsReceivingPackets.clear();
		//m_ConnectionsReceivingErrors.clear();
		//m_ConnectionsStarting.clear();

		int result = WSAPoll(m_ListeningSocketFD, 1, 0);
		if (result == SOCKET_ERROR)
		{
			UE_CORE_ERROR("Winsock WSAPoll() failed: {0}", WSAGetLastError());
			return -1;
		}
		else if (result == 0)
		{
			return 0;
		}

		// Check for connection and add it to the connection
		WSAPOLLFD& ListeningSocketFD = m_ListeningSocketFD[0];
		if (ListeningSocketFD.revents & POLLRDNORM)
		{
			IPEndpoint SenderIPEndpoint;
			Packet ReceivedPacket;
			
			int result = m_ListeningSocket->RecvFrom(SenderIPEndpoint, ReceivedPacket);
			if (result == UE_VALUE_ERROR)
			{
				UE_CORE_ERROR("Winsock WSAPoll() failed: RecvFrom() failed");
				return -1;
			}

			if (ReceivedPacket.GetPacketType() == Packet::PacketType::ConnectionRequest)
			{
				// Queue new connection to be started
				Ref<Connection> ConnectionStarting = CreateRef<Connection>();
				ConnectionStarting->GetIPEndpoint()->SetIp(SenderIPEndpoint.GetIp());
				ConnectionStarting->GetIPEndpoint()->SetPort(SenderIPEndpoint.GetPort());
				ConnectionStarting->SetConnectionState(Connection::ConnectionState::SendingChallenge);

				ConnectionStarting->AddIncomingPacket(CreateRef<Packet>(ReceivedPacket));
				
				m_Connections.insert({ SenderIPEndpoint, ConnectionStarting });
				m_ConnectionsStarting.push_back(ConnectionStarting);
				return 0;
			}

			if (m_Connections.find(SenderIPEndpoint) == m_Connections.end())
			{
				// Packet was received by unknown and should be ignored
				return 0;
			}

			// Retrieve connection
			Ref<Connection> CurrentConnection = m_Connections.at(SenderIPEndpoint);

			Packet::PacketType ReceivedPacketType = ReceivedPacket.GetPacketType();
			bool ValidPacket = (ReceivedPacketType > Packet::PacketType::First && ReceivedPacketType < Packet::PacketType::Last);
			if (ValidPacket)
			{
				// Queue connection to be processed
				m_ConnectionsReceivingPackets.push_back(CurrentConnection);
				return 0;
			}
			else if (ValidPacket && CurrentConnection->GetConnectionState() != Connection::ConnectionState::Connected)
			{
				m_ConnectionsStarting.push_back(CurrentConnection);
				return 0;
			}
			else
			{
				// Queue connection to be processed for errors
				m_ConnectionsReceivingErrors.push_back(CurrentConnection);
				return 0;
			}
		}

		return 0;
	}

	void WinsockConnectionManager::CloseConnection(int connectionIndex)
	{
	}
}