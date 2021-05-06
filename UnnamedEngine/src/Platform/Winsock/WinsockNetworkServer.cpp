#include "uepch.h"
#include "Platform/Winsock/WinsockNetworkServer.h"

#include "Events/NetworkEvent.h"

#include <winsock2.h>
#include <WS2tcpip.h>

namespace UE
{
	WinsockNetworkServer::~WinsockNetworkServer()
	{
	}

	void WinsockNetworkServer::Init(std::string port)
	{
		// Initialize Socket on listening mode at specified port and bind it
		m_ListeningSocket = Socket::Create();
		int result = m_ListeningSocket->Init(port);
		if (result == SOCKET_ERROR)
		{
			UE_CORE_ERROR("Failed to initialize Server Socket!");
			return;
		}
		result = m_ListeningSocket->Block(false);
		if (result == SOCKET_ERROR)
		{
			UE_CORE_ERROR("Failed to set Server Socket to non-blocking mode!");
			return;
		}

		WSAPOLLFD t_ListeningSocketFD;
		t_ListeningSocketFD.fd = *(SOCKET*)m_ListeningSocket->GetNativeSocket();
		t_ListeningSocketFD.events = POLLRDNORM;
		t_ListeningSocketFD.revents = 0;
		m_MasterFD.push_back(t_ListeningSocketFD);
	}

	void WinsockNetworkServer::Shutdown()
	{
		// Disconnect every client and close the listening socket
		m_ListeningSocket->Close();
	}

	void WinsockNetworkServer::OnUpdate()
	{
		m_UseFD = m_MasterFD;
		
		int result = WSAPoll(m_UseFD.data(), m_UseFD.size(), 0);
		if (result == SOCKET_ERROR)
		{
			UE_CORE_ERROR("Winsock WSAPoll() failed: {0}", WSAGetLastError());
			return;
		}
		else if (result == 0)
		{
			return;
		}

		// Check for connection and add it to the connections
		WSAPOLLFD& t_ListeningSocketFD = m_UseFD[0];
		if (t_ListeningSocketFD.revents & POLLRDNORM)
		{
			Ref<Socket> t_ConnectedSocket = Socket::Create();
			t_ConnectedSocket->Init();
			//t_ConnectedSocket->Block(false);
			int error = t_ConnectedSocket->Accept(m_ListeningSocket);
			if (error != SOCKET_ERROR)
			{
				WSAPOLLFD t_ConnectedSocketFD;
				t_ConnectedSocketFD.fd = *(SOCKET*)t_ConnectedSocket->GetNativeSocket();
				t_ConnectedSocketFD.events = POLLRDNORM;
				t_ConnectedSocketFD.revents = 0;
				m_MasterFD.push_back(t_ConnectedSocketFD);
				m_Connections.push_back(Connection(t_ConnectedSocket));

				ClientConnectedEvent event(t_ConnectedSocket->GetIP(), t_ConnectedSocket->GetPort());
				m_EventCallbackFn(event);
			}
		}

		for (int i = m_UseFD.size() - 1; i >= 1; i--)
		{
			m_ConnectionIndex = i - 1;
			Connection& t_CurrentConnection = m_Connections[m_ConnectionIndex];

			if (m_UseFD[i].revents & POLLERR)
			{
				UE_CORE_ERROR("Disconnection of {0}:{1} was caused by an error!", t_CurrentConnection.m_Socket->GetIP(), t_CurrentConnection.m_Socket->GetPort());
				CloseConnection(m_ConnectionIndex);
				continue;
			}

			if (m_UseFD[i].revents & POLLHUP)
			{
				ClientDisconectedEvent event(t_CurrentConnection.m_Socket->GetIP(), t_CurrentConnection.m_Socket->GetPort());
				m_EventCallbackFn(event);
				CloseConnection(m_ConnectionIndex);
				continue; 
			}

			if (m_UseFD[i].revents & POLLRDNORM)
			{
				int bytesReceived = 0;

				if (t_CurrentConnection.m_Task == Packet::PacketTask::ProcessPacketSize)
				{
					bytesReceived = recv(m_UseFD[i].fd, (char*)&t_CurrentConnection.m_PacketSize + t_CurrentConnection.m_ExtractionOffset, sizeof(uint16_t) - t_CurrentConnection.m_ExtractionOffset, 0);
				}
				else
				{
					bytesReceived = recv(m_UseFD[i].fd, (char*)&t_CurrentConnection.m_Buffer + t_CurrentConnection.m_ExtractionOffset, t_CurrentConnection.m_PacketSize - t_CurrentConnection.m_ExtractionOffset, 0);
				}

				if (bytesReceived == 0)
				{
					ClientDisconectedEvent event(t_CurrentConnection.m_Socket->GetIP(), t_CurrentConnection.m_Socket->GetPort());
					m_EventCallbackFn(event);
					CloseConnection(m_ConnectionIndex);
					continue;
				}

				if (bytesReceived == SOCKET_ERROR)
				{
					int error = WSAGetLastError();
					if (error != WSAEWOULDBLOCK)
					{
						UE_CORE_ERROR("Disconnection of {0}:{1} was caused by an error: {2}", t_CurrentConnection.m_Socket->GetIP(), t_CurrentConnection.m_Socket->GetPort(), error);
						CloseConnection(m_ConnectionIndex);
						continue;
					}
				}

				if (bytesReceived > 0)
				{
					t_CurrentConnection.m_ExtractionOffset += bytesReceived;
					if (t_CurrentConnection.m_Task == Packet::PacketTask::ProcessPacketSize)
					{
						if (t_CurrentConnection.m_ExtractionOffset == sizeof(uint16_t))
						{
							t_CurrentConnection.m_PacketSize = UE_NTOHS(t_CurrentConnection.m_PacketSize);
							if (t_CurrentConnection.m_PacketSize > UE_MAX_PACKET_SIZE)
							{
								UE_CORE_ERROR("Disconnection of {0}{1} was caused by and error: Packet size was too large!", t_CurrentConnection.m_Socket->GetIP(), t_CurrentConnection.m_Socket->GetPort());
								CloseConnection(m_ConnectionIndex);
								continue;
							}
						}
						t_CurrentConnection.m_ExtractionOffset = 0;
						t_CurrentConnection.m_Task = Packet::PacketTask::ProcessPacketContents;
					}
					else
					{
						if (t_CurrentConnection.m_ExtractionOffset == t_CurrentConnection.m_PacketSize)
						{
							Packet t_Packet;
							t_Packet.m_Buffer.resize(t_CurrentConnection.m_PacketSize);
							memcpy(&t_Packet.m_Buffer[0], t_CurrentConnection.m_Buffer, t_CurrentConnection.m_PacketSize);



							if (!ProcessPacket(t_Packet))
							{
								UE_CORE_ERROR("Disconnection of {0}{1} was caused by and error: Failed to process packet!", t_CurrentConnection.m_Socket->GetIP(), t_CurrentConnection.m_Socket->GetPort());
								CloseConnection(m_ConnectionIndex);
								continue;
							}

							t_CurrentConnection.m_PacketSize = 0;
							t_CurrentConnection.m_ExtractionOffset = 0;
							t_CurrentConnection.m_Task = Packet::PacketTask::ProcessPacketSize;
						}
					}
				}
			}
		}
	}

	void WinsockNetworkServer::CloseConnection(int socketIndex)
	{
		Connection t_CurrentConnection = m_Connections[socketIndex];
		m_MasterFD.erase(m_MasterFD.begin() + (socketIndex + 1));
		m_UseFD.erase(m_UseFD.begin() + (socketIndex + 1));
		t_CurrentConnection.m_Socket->Close();
		m_Connections.erase(m_Connections.begin() + socketIndex);
	}

	bool WinsockNetworkServer::ProcessPacket(Packet& packet)
	{
		switch (packet.GetPacketType())
		{
		case Packet::PacketType::CharArray:
		{
			std::string t_Message;
			packet >> t_Message;
			UE_CORE_INFO("Message: {0}", t_Message);
			break;
		}
		default:
		{
			UE_CORE_ERROR("Unknown PacketType!");
			return false;
		}
		}

		return true;
	}
}