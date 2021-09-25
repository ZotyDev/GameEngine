#include "uepch.h"
#include "Platform/Winsock/WinsockSocket.h"

#include "Platform/Winsock/WinsockHelper.h"

namespace UE
{
	WinsockSocket::WinsockSocket()
		: m_Socket(INVALID_SOCKET)
	{}

	WinsockSocket::~WinsockSocket()
	{

	}

	int WinsockSocket::Init()
	{
		// Create UDP socket
		m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (m_Socket == INVALID_SOCKET)
		{
			UE_CORE_ERROR("Winsock socket() failed: {0}", StringfyErrorCode(WSAGetLastError()));
			return -1;
		}

		return 0;
	}

	void WinsockSocket::Shutdown()
	{
		closesocket(m_Socket);
	}

	int WinsockSocket::Bind(IPEndpoint ipEndpoint)
	{
		sockaddr_in ReceiveAddr;
		ReceiveAddr.sin_family = AF_INET;
		ReceiveAddr.sin_port = UE_HTONS(ipEndpoint.GetUPort());
		ReceiveAddr.sin_addr.S_un.S_addr = inet_addr(ipEndpoint.GetIp().c_str());

		int result = bind(m_Socket, (sockaddr*)&ReceiveAddr, sizeof(ReceiveAddr));
		if (result == SOCKET_ERROR)
		{
			UE_CORE_ERROR("Winsock bind() failed: {0}", StringfyErrorCode(WSAGetLastError()));
			return -1;
		}

		return 0;
	}

	int WinsockSocket::Block(bool block)
	{
		if (block == m_IsBlocking)
		{
			return 0;
		}

		unsigned long blocking = block ? 0 : 1;
		int resut = ioctlsocket(m_Socket, FIONBIO, &blocking);
		if (resut == SOCKET_ERROR)
		{
			UE_CORE_ERROR("Winsock failed to put Socket {0} on {1} mode: {2}", m_Socket, block ? "blocking" : "non-blocking", StringfyErrorCode(WSAGetLastError()));
			return -1;
		}

		m_IsBlocking = block;

		return 0;
	}

	int WinsockSocket::SendTo(IPEndpoint destination, const void* data, int numberOfBytes, int& bytesSent)
	{
		sockaddr_in DestinationAddr;
		DestinationAddr.sin_family = AF_INET;
		DestinationAddr.sin_port = UE_HTONS(destination.GetUPort());
		DestinationAddr.sin_addr.S_un.S_addr = inet_addr(destination.GetIp().c_str());
		
		bytesSent = sendto(m_Socket, (const char*)data, numberOfBytes, 0, (sockaddr*)&DestinationAddr, sizeof(DestinationAddr));

		if (bytesSent == SOCKET_ERROR)
		{
			UE_CORE_ERROR("Winsock sendto() failed: {0}", StringfyErrorCode(WSAGetLastError()));
			return -1;
		}

		return 0;
	}

	int WinsockSocket::RecvFrom(IPEndpoint& sender, void* data, int numberOfBytes, int& bytesReceived)
	{
		sockaddr_in SenderAddr;
		int SenderAddrSize = sizeof(SenderAddr);

		bytesReceived = recvfrom(m_Socket, (char*)data, numberOfBytes, 0, (sockaddr*)&SenderAddr, &SenderAddrSize);

		if (bytesReceived == 0)
		{
			return -1;
		}

		if (bytesReceived == SOCKET_ERROR)
		{
			UE_CORE_ERROR("Winsock recvfrom failed: {0}", StringfyErrorCode(WSAGetLastError()));
			return -1;
		}

		sender.SetIp(inet_ntoa(SenderAddr.sin_addr));
		sender.SetPort(SenderAddr.sin_port);

		return 0;
	}

	int WinsockSocket::SendAllTo(IPEndpoint destination, const void* data, int numberOfBytes) 
	{
		int TotalBytesSent = 0;

		while (TotalBytesSent < numberOfBytes)
		{
			int BytesRemaining = numberOfBytes - TotalBytesSent;
			int BytesSent = 0;
			char* BufferOffset = (char*)data + TotalBytesSent;
			int result = SendTo(destination, BufferOffset, numberOfBytes, BytesSent);
			if (result == UE_VALUE_ERROR)
			{
				UE_CORE_ERROR("UnnamedEngine SendAllTo() failed");
				return -1;
			}
			TotalBytesSent += BytesSent;
		}

		return 0;
	}

	int WinsockSocket::RecvAllFrom(IPEndpoint& sender, void* data, int numberOfBytes)
	{
		int TotalBytesReceived = 0;

		while (TotalBytesReceived < numberOfBytes)
		{
			int BytesRemaining = numberOfBytes - TotalBytesReceived;
			int BytesReceived = 0;
			char* BufferOffset = (char*)data + TotalBytesReceived;
			int result = RecvFrom(sender, BufferOffset, numberOfBytes, BytesReceived);
			if (result == UE_VALUE_ERROR)
			{
				UE_CORE_ERROR("UnnamedEngine RecvAllFrom() failed");
				return -1;
			}
			TotalBytesReceived += BytesReceived;
		}

		return 0;
	}

	/*int WinsockSocket::SendTo(IPEndpoint destination, Packet& packet)
	{
		uint16_t EncodedSize = UE_HTONS(packet.m_Buffer.size());
		int result = SendAllTo(destination, &EncodedSize, sizeof(uint16_t));
		if (result == UE_VALUE_ERROR)
		{
			UE_CORE_ERROR("UnnamedEngine SendTo() failed: could not send size of packet");
			return -1;
		}

		result = SendAllTo(destination, packet.m_Buffer.data(), packet.m_Buffer.size());
		if (result == UE_VALUE_ERROR)
		{
			UE_CORE_ERROR("UnnamedEngine SendTo() failed: could not send data of packet");
			return -1;
		}

		return 0;
	}

	int WinsockSocket::RecvFrom(IPEndpoint& from, Packet& packet)
	{
		packet.Clear();
		
		uint16_t EncodedSize = 0;
		int result = RecvAllFrom(from, &EncodedSize, sizeof(uint16_t));
		if (result == UE_VALUE_ERROR)
		{
			UE_CORE_ERROR("UnnamedEngine RecvFrom() failed: could not receive size of packet");
			return -1;
		}

		uint16_t BufferSize = UE_HTONS(EncodedSize);

		if (BufferSize > UE_MAX_PACKET_SIZE)
		{
			UE_CORE_ERROR("UnnamedEngine RecvFrom() failed: packet exceeds maximum size");
			return -1;
		}

		packet.m_Buffer.resize(BufferSize);
		result = RecvAllFrom(from, &packet.m_Buffer[0], BufferSize);
		if (result == UE_VALUE_ERROR)
		{
			UE_CORE_ERROR("UnnamedEngine RecvFrom() failed: could not receive data of packet");
			return -1;
		}

		return 0;
	}*/

	int WinsockSocket::Poll()
	{
		m_IsReceivingPackets = false;
		m_IsReceivingErrors = false;

		WSAPOLLFD ListeningSocketFD[1];
		ListeningSocketFD[0].fd = *(SOCKET*)GetNativeSocket();
		ListeningSocketFD[0].events = POLLRDNORM;
		ListeningSocketFD[0].revents = 0;

		int result = WSAPoll(ListeningSocketFD, 1, 0);
		if (result == SOCKET_ERROR)
		{
			UE_CORE_ERROR("Winsock WSAPoll() failed: {0}", StringfyErrorCode(WSAGetLastError()));
			return -1;
		}
		else if (result == 0)
		{
			return 0;
		}

		if (ListeningSocketFD[0].revents & POLLERR)
		{
			m_IsReceivingErrors = true;
		}

		if (ListeningSocketFD[0].revents & POLLRDNORM)
		{
			m_IsReceivingPackets = true;
		}

		return result;
	}

	void* WinsockSocket::GetNativeSocket() const
	{
		return (void*)&m_Socket;
	}
}