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
		virtual ~WinsockSocket() override;

		virtual int Init() override;
		virtual int Init(std::string port) override;
		virtual int Block(bool block) override;
		virtual int Connect(std::string ip, std::string port) override;
		virtual int Accept(Ref<Socket> listeningSocket) override;
		virtual int Send(const void* data, int numberOfBytes, int& bytesSent) override;
		virtual int Recv(void* data, int numberOfBytes, int& bytesReceived) override;
		virtual int SendAll(const void* data, int numberOfBytes) override;
		virtual int RecvAll(void* data, int numberOfBytes) override;
		virtual int Send(Packet& packet) override;
		virtual int Recv(Packet& packet) override;

		virtual void Close() override;

		virtual void* GetNativeSocket() const override { return (void*)&m_Socket; };

		virtual std::string GetIP() const override { return m_IP; };
		virtual unsigned short GetPort() const override { return m_Port; };

		// Sockets are unique and should not be copied
		WinsockSocket(const WinsockSocket&) = delete;
		WinsockSocket& operator = (const WinsockSocket&) = delete;

	private:
		SOCKET m_Socket;
		bool m_IsBlocking;
		std::string m_IP;
		unsigned short m_Port;
	};
}