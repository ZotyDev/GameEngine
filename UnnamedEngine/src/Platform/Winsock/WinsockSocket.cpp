#include "Networking/Socket.hpp"

#include <winsock2.h>
#include <WS2tcpip.h>

#include "Winsock/WinsockHelper.hpp"

#include "Core/PlatformIndependenceLayer/PlatformUtilities.hpp"

namespace UE
{
    Socket::Socket()
    {
        m_NativeSocket = (void*)new SOCKET(INVALID_SOCKET);
    }

    Socket::~Socket()
    {
        Shutdown();
        delete m_NativeSocket;
    }

    UEResult<> Socket::Init()
    {
        SOCKET Socket = (SOCKET)m_NativeSocket;

        // Create UDP socket
        Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (Socket == INVALID_SOCKET)
        {
            UE_LOG_CORE_ERROR("Winsock socket() failed: {0}", StringfyErrorCode(WSAGetLastError()));
            return UEResult<>::Error;
        }

        return UEResult<>::Success;
    }

    UEResult<> Socket::Shutdown()
    {
        SOCKET Socket = (SOCKET)m_NativeSocket;

        closesocket(Socket);

        return UEResult<>::Success;
    }

    UEResult<> Socket::Bind(IPEndpoint endpoint)
    {
        SOCKET Socket = (SOCKET)m_NativeSocket;

        sockaddr_in ReceiveAddress;
        ReceiveAddress.sin_family = AF_INET;
        ReceiveAddress.sin_port = PlatformUtilities::HostToNetwork16(endpoint.GetUPort());
        ReceiveAddress.sin_addr.S_un.S_addr = inet_addr(endpoint.IP.c_str());

        UEInt32 Result = bind(Socket, (sockaddr*)&ReceiveAddress, sizeof(ReceiveAddress));
        if (Result == SOCKET_ERROR)
        {
            UE_LOG_CORE_ERROR("Winsock bind() failed {0}", StringfyErrorCode(WSAGetLastError()));
            return UEResult<>::Error;
        }

        return UEResult<>::Success;
    }

    UEResult<> Socket::Block(UEBool block)
    {
        SOCKET Socket = (SOCKET)m_NativeSocket;

        if (block == m_IsBlocking)
        {
            return UEResult<>::Success;
        }

        unsigned long Blocking = block ? 0 : 1;
        UEInt32 Result = ioctlsocket(Socket, FIONBIO, &Blocking);
        if (Result == SOCKET_ERROR)
        {
            UE_LOG_CORE_ERROR("Winsock failed to put Socket {0} on {1} mode: {2}", Socket, block ? "blocking" : "non-blocking", StringfyErrorCode(WSAGetLastError()));
            return UEResult<>::Error;
        }

        m_IsBlocking = block;

        return UEResult<>::Success;
    }

    UEResult<> Socket::SendTo(IPEndpoint destination, const void* data, UEUint32 numberOfBytes, UEUint32& bytesSent)
    {
        SOCKET Socket = (SOCKET)m_NativeSocket;

        sockaddr_in DestinationAddress;
		DestinationAddress.sin_family = AF_INET;
		DestinationAddress.sin_port = (UEUint16)PlatformUtilities::HostToNetwork16(destination.GetUPort());
		DestinationAddress.sin_addr.S_un.S_addr = inet_addr(destination.IP.c_str());

		bytesSent = sendto(Socket, (const char*)data, numberOfBytes, 0, (sockaddr*)&DestinationAddress, sizeof(DestinationAddress));

		if (bytesSent == SOCKET_ERROR)
		{
			UE_LOG_CORE_ERROR("Winsock sendto() failed: {0}", StringfyErrorCode(WSAGetLastError()));
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
    }

    UEResult<> Socket::ReceiveFrom(IPEndpoint& sender, void* data, UEUint32 numberOfBytes, UEUint32& bytesReceived)
    {
        SOCKET Socket = (SOCKET)m_NativeSocket;

        sockaddr_in SenderAddress;
		UEInt32 SenderAddressSize = sizeof(SenderAddress);

		bytesReceived = recvfrom(Socket, (char*)data, numberOfBytes, 0, (sockaddr*)&SenderAddress, &SenderAddressSize);

		if (bytesReceived == 0)
		{
			return UEResult<>::Error;
		}

		if (bytesReceived == SOCKET_ERROR)
		{
			UE_LOG_CORE_ERROR("Winsock recvfrom failed: {0}", StringfyErrorCode(WSAGetLastError()));
			return UEResult<>::Error;
		}

		sender.IP = inet_ntoa(SenderAddress.sin_addr);
		sender.SetUPort(SenderAddress.sin_port);

		return UEResult<>::Success;
    }

    UEResult<> Socket::SendAllTo(IPEndpoint destination, const void* data, UEUint32 numberOfBytes)
    {
        int TotalBytesSent = 0;

		while (TotalBytesSent < numberOfBytes)
		{
			UEUint32 BytesRemaining = numberOfBytes - TotalBytesSent;
			UEUint32 BytesSent = 0;
			UEChar* BufferOffset = (UEChar*)data + TotalBytesSent;
			UEResult<> Result = SendTo(destination, BufferOffset, numberOfBytes, BytesSent);
			if (Result.Result == UEResult<>::Error)
			{
				UE_LOG_CORE_ERROR("UnnamedEngine SendAllTo() failed");
				return UEResult<>::Error;
			}
			TotalBytesSent += BytesSent;
		}

		return UEResult<>::Success;
    }

    UEResult<> Socket::ReceiveAllFrom(IPEndpoint& sender, void* data, UEUint32 numberOfBytes)
    {
        UEUint32 TotalBytesReceived = 0;

		while (TotalBytesReceived < numberOfBytes)
		{
			UEUint32 BytesRemaining = numberOfBytes - TotalBytesReceived;
			UEUint32 BytesReceived = 0;
			UEChar* BufferOffset = (UEChar*)data + TotalBytesReceived;
			UEResult<> Result = ReceiveFrom(sender, BufferOffset, numberOfBytes, BytesReceived);
			if (Result.Result == UEResult<>::Error)
			{
				UE_LOG_CORE_ERROR("UnnamedEngine RecvAllFrom() failed");
				return UEResult<>::Error;
			}
			TotalBytesReceived += BytesReceived;
		}

		return UEResult<>::Success;
    }

    UEResult<UEInt32> Socket::Poll()
    {
        m_IsReceivingPackets = false;
		m_IsReceivingErrors = false;

		WSAPOLLFD ListeningSocketFD[1];
		ListeningSocketFD[0].fd = (SOCKET)m_NativeSocket;
		ListeningSocketFD[0].events = POLLRDNORM;
		ListeningSocketFD[0].revents = 0;

		UEInt32 Result = WSAPoll(ListeningSocketFD, 1, 0);
		if (Result == SOCKET_ERROR)
		{
			UE_LOG_CORE_ERROR("Winsock WSAPoll() failed: {0}", StringfyErrorCode(WSAGetLastError()));
			return UEResult<UEInt32>::Error;
		}
		else if (Result == 0)
		{
			return UEResult<UEInt32>::Success;
		}

		if (ListeningSocketFD[0].revents & POLLERR)
		{
			m_IsReceivingErrors = true;
		}

		if (ListeningSocketFD[0].revents & POLLRDNORM)
		{
			m_IsReceivingPackets = true;
		}

		return UEResult<UEInt32>(Result, UEResult<UEInt32>::Success);
    }
}
