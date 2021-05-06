#pragma once

#include "Network/NetworkAPI.h"
#include "Network/Packet.h"

namespace UE
{
	class Socket
	{
	public:
		virtual ~Socket() = default;

		virtual int Init() = 0;
		virtual int Init(std::string port) = 0;
		virtual int Block(bool block) = 0;
		virtual int Connect(std::string ip, std::string port) = 0;;
		virtual int Accept(Ref<Socket> listeningSocket) = 0;
		virtual int Send(const void* data, int numberOfBytes, int& bytesSent) = 0;
		virtual int Recv(void* data, int numberOfBytes, int& bytesReceived) = 0;
		virtual int SendAll(const void* data, int numberOfBytes) = 0;
		virtual int RecvAll(void* data, int numberOfBytes) = 0;
		virtual int Send(Packet& packet) = 0;
		virtual int Recv(Packet& packet) = 0;

		virtual void Close() = 0;

		virtual void* GetNativeSocket() const = 0;

		virtual std::string GetIP() const = 0;
		virtual unsigned short GetPort() const = 0;

		static Ref<Socket> Create();
	};
}