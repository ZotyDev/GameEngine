#include "uepch.h"
#include "Platform/Winsock/WinsockSocket.h"

#include <winsock2.h>
#include <WS2tcpip.h>

namespace UE
{
	WinsockSocket::WinsockSocket()
		: m_Socket(INVALID_SOCKET), m_IsBlocking(true), m_IP(""), m_Port(0)
	{
	}

	WinsockSocket::~WinsockSocket()
	{}

	int WinsockSocket::Init()
	{
		// Create the socket
		m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (m_Socket == INVALID_SOCKET)
		{
			UE_CORE_ERROR("Winsock socket() failed: {0}", WSAGetLastError());
			return -1;
		}

		return 0;
	}

	int WinsockSocket::Init(std::string port)
	{
		/*struct addrinfo* result = NULL;
		struct addrinfo hints;

		/* 
		*	AF_INET = IPV4 | AF_INET6 = IPV6
		*	SOCK_STREAM = socket is in streaming mode
		*	IPPROTO_TCP = socket is using TCP protocol
		*/
		/*ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		// Request IP address
		int error = getaddrinfo(NULL, port.c_str(), &hints, &result);
		if (error == SOCKET_ERROR)
		{
			UE_CORE_ERROR("Winsock getaddrinfo() failed: {0}", WSAGetLastError());
			return -1;
		}

		// Create the socket
		m_Socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (m_Socket == INVALID_SOCKET)
		{
			UE_CORE_ERROR("Winsock socket() failed: {0}", WSAGetLastError());
			return -1;
		}*/

		m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (m_Socket == INVALID_SOCKET)
		{
			UE_CORE_ERROR("Winsock socket() failed: {0}", WSAGetLastError());
			return -1;
		}

		sockaddr_in service;
		service.sin_family = AF_INET;
		service.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		service.sin_port = (unsigned short)std::strtoul(port.c_str(), nullptr, 0);

		int error = bind(m_Socket, (SOCKADDR*)&service, sizeof(service));
		if (error == SOCKET_ERROR)
		{
			UE_CORE_ERROR("Winsock bind() failed: {0}", WSAGetLastError());
			closesocket(m_Socket);
			return -1;
		}

		error = listen(m_Socket, SOMAXCONN);
		if (error == SOCKET_ERROR)
		{
			UE_CORE_ERROR("Winsock listen() failed: {0}", WSAGetLastError());
			closesocket(m_Socket);
			return -1;
		}

		UE_CORE_INFO("Listening at: {0}", inet_ntoa(service.sin_addr));

		//freeaddrinfo(result);

		return 0;
	}

	int WinsockSocket::Block(bool block)
	{
		if (block == m_IsBlocking)
		{
			return 0;
		}

		unsigned long blocking = block ? 0 : 1;
		int error = ioctlsocket(m_Socket, FIONBIO, &blocking);
		if (error == SOCKET_ERROR)
		{
			UE_CORE_ERROR("Winsock failed to put Socket {0} on {1} mode: {2}", m_Socket, block ? "blocking" : "non-blocking", WSAGetLastError());
			return -1;
		}

		m_IsBlocking = block;

		return 0;
	}

	int WinsockSocket::Connect(std::string ip, std::string port)
	{
		struct sockaddr_in server;

		/*
		*	AF_INET = IPV4 | AF_INET6 = IPV6
		*/
		server.sin_family = AF_INET;
		server.sin_port = (unsigned short)std::strtoul(port.c_str(), nullptr, 0);
		server.sin_addr.S_un.S_addr = inet_addr(ip.c_str());

		int error = connect(m_Socket, (struct sockaddr*)&server, sizeof(server));
		if (error == SOCKET_ERROR)
		{
			UE_CORE_ERROR("Winsock connect() failed: {0}", WSAGetLastError());
			return -1;
		}

		m_IP = inet_ntoa(server.sin_addr);
		m_Port = server.sin_port;

		return 0;
	}

	int WinsockSocket::Accept(Ref<Socket> listeningSocket)
	{
		struct sockaddr_in ptr;
		int size = sizeof(ptr);

		m_Socket = WSAAccept(*(SOCKET*)listeningSocket->GetNativeSocket(), (struct sockaddr*)&ptr, &size, NULL, NULL);
		if (m_Socket == INVALID_SOCKET)
		{
			UE_CORE_ERROR("Winsock WSAAccept() failed: {0}", WSAGetLastError());
			return -1;
		}

		m_IP = inet_ntoa(ptr.sin_addr);
		m_Port = ptr.sin_port;

		return 0;
	}

	int WinsockSocket::Send(const void* data, int numberOfBytes, int& bytesSent)
	{
		bytesSent = send(m_Socket, (const char*)data, numberOfBytes, NULL);

		if (bytesSent == SOCKET_ERROR)
		{
			UE_CORE_ERROR("Winsock send() failed: {0}", WSAGetLastError());
			return -1;
		}

		return 0;
	}

	int WinsockSocket::Recv(void* data, int numberOfBytes, int& bytesReceived)
	{
		bytesReceived = recv(m_Socket, (char*)data, numberOfBytes, NULL);

		if (bytesReceived == 0)
		{
			return -1;
		}

		if (bytesReceived == SOCKET_ERROR)
		{
			UE_CORE_ERROR("Winsock recv() faield: {0}", WSAGetLastError());
			return -1;
		}

		return 0;
	}

	int WinsockSocket::SendAll(const void* data, int numberOfBytes)
	{
		int t_TotalBytesSent = 0;

		while (t_TotalBytesSent < numberOfBytes)
		{
			int t_BytesRemaining = numberOfBytes - t_TotalBytesSent;
			int t_BytesSent = 0;
			char* t_BufferOffset = (char*)data + t_TotalBytesSent;
			int result = Send(t_BufferOffset, t_BytesRemaining, t_BytesSent);
			if (result == SOCKET_ERROR)
			{
				UE_CORE_ERROR("UnnamedEngine SendAll() failed!");
				return -1;
			}
			t_TotalBytesSent += t_BytesSent;
		}
		return 0;
	}

	int WinsockSocket::RecvAll(void* data, int numberOfBytes)
	{
		int t_TotalBytesReceived = 0;

		while (t_TotalBytesReceived < numberOfBytes)
		{
			int t_BytesRemaining = numberOfBytes - t_TotalBytesReceived;
			int t_BytesReceived = 0;
			char* t_BufferOffset = (char*)data + t_TotalBytesReceived;
			int result = Recv(t_BufferOffset, t_BytesRemaining, t_BytesReceived);
			if (result == SOCKET_ERROR)
			{
				UE_CORE_ERROR("UnnamedEngine RecvAll() failed!");
				return -1;
			}
			t_TotalBytesReceived += t_BytesReceived;
		}
		return 0;
	}

	int WinsockSocket::Send(Packet& packet)
	{
		uint16_t t_EncodedSize = UE_HTONS(packet.m_Buffer.size());
		int result = SendAll(&t_EncodedSize, sizeof(uint16_t));
		if (result == SOCKET_ERROR)
		{
			UE_CORE_ERROR("UnnamedEngine Send() failed: could not send size of packet");
			return -1;
		}

		result = SendAll(packet.m_Buffer.data(), packet.m_Buffer.size());
		if (result == SOCKET_ERROR)
		{
			UE_CORE_ERROR("UnnamedEngine Send() failed: could not send data of packet");
			return -1;
		}
	}

	int WinsockSocket::Recv(Packet& packet)
	{
		packet.Clear();

		uint16_t t_EncondedSize = 0;
		int result = RecvAll(&t_EncondedSize, sizeof(uint16_t));
		if (result == SOCKET_ERROR)
		{
			UE_CORE_ERROR("UnnamedEngine Recv() failed: could not get size of packet");
			return -1;
		}

		uint16_t t_BufferSize = UE_NTOHS(t_EncondedSize);

		if (t_BufferSize > UE_MAX_PACKET_SIZE)
		{
			UE_CORE_ERROR("UnnamedEngine Recv() failed: packet exceeds maximum size");
			return -1;
		}

		packet.m_Buffer.resize(t_BufferSize);
		result = RecvAll(&packet.m_Buffer[0], t_BufferSize);
		if (result == SOCKET_ERROR)
		{
			UE_CORE_ERROR("UnnamedEngine Recv() failed: could not get data of packet");
			return -1;
		}

		return 0;
	}

	void WinsockSocket::Close()
	{
		int result = shutdown(m_Socket, SD_SEND);
		if (result == SOCKET_ERROR)
		{
			UE_CORE_ERROR("Winsock shutdown() failed: {0}", WSAGetLastError());
			return;
		}
		closesocket(m_Socket);
	}

}