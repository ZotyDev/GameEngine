#pragma once

#include "Core/Base.h"

#include "Network/IPEndpoint.h"
#include "Network/Packet.h"

namespace UE
{
	class Socket
	{
	public:
		Socket() = default;
		virtual ~Socket() = default;

		virtual int Init() = 0;
		virtual void Shutdown() = 0;
		virtual int Bind(IPEndpoint ipEndpoint) = 0;

		virtual int Block(bool block) = 0;

		virtual int SendTo(IPEndpoint destination, const void* data, int numberOfBytes, int& bytesSent) = 0;
		virtual int RecvFrom(IPEndpoint& sender, void* data, int numberOfBytes, int& bytesReceived) = 0;

		virtual int SendAllTo(IPEndpoint destination, const void* data, int numberOfBytes) = 0;
		virtual int RecvAllFrom(IPEndpoint& sender, void* data, int numberOfBytes) = 0;

		virtual int SendTo(IPEndpoint destination, Packet& packet) = 0;
		virtual int RecvFrom(IPEndpoint& sender, Packet& packet) = 0;

		virtual int Poll() = 0;

		virtual void* GetNativeSocket() const = 0;

		const bool IsReceivingPackets() { return m_IsReceivingPackets; }
		const bool IsReceivingErrors() { return m_IsReceivingErrors; }

		static Scope<Socket> Create();
	protected:
		bool m_IsReceivingPackets = false;
		bool m_IsReceivingErrors = false;
	};
}