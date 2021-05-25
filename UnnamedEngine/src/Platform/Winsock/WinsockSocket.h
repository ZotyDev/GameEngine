#pragma once

#include "Network/Socket.h"

#include <winsock2.h>
#include <WS2tcpip.h>

namespace UE
{
	class WinsockSocket : public Socket
	{
	public:
		WinsockSocket();
		virtual ~WinsockSocket();

		virtual int Init() override;
		virtual void Shutdown() override;
		virtual int Bind(IPEndpoint ipEndpoint) override;

		virtual int Block(bool block) override;

		virtual int SendTo(IPEndpoint destination, const void* data, int numberOfBytes, int& bytesSent) override;
		virtual int RecvFrom(IPEndpoint& sender, void* data, int numberOfBytes, int& bytesReceived) override;

		virtual int SendAllTo(IPEndpoint destination, const void* data, int numberOfBytes) override;
		virtual int RecvAllFrom(IPEndpoint& sender, void* data, int numberOfBytes) override;

		virtual int SendTo(IPEndpoint destination, Packet& packet) override;
		virtual int RecvFrom(IPEndpoint& sender, Packet& packet) override;

		virtual int Poll() override;

		virtual void* GetNativeSocket() const override;

	private:
		SOCKET m_Socket;
		bool m_IsBlocking = true;
		bool m_IsLingering = true;
	};
}