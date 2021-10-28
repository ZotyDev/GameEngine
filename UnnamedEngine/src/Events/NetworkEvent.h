#pragma once

#include "Events/Event.h"
#include "Network/IPEndpoint.h"
//#include "Network/Packet.h"

namespace UE
{
	class NetworkEvent : public Event
	{
	public:
		IPEndpoint GetIPEndpoint() const { return m_IPEndpoint; }

		EVENT_CLASS_CATEGORY(EventCategoryNetwork)
	protected:
		NetworkEvent(IPEndpoint ipEndpoint)
			: m_IPEndpoint(ipEndpoint)
		{
		}

		IPEndpoint m_IPEndpoint;
	};

	class ClientConnectedEvent : public NetworkEvent
	{
	public:
		ClientConnectedEvent(IPEndpoint ipEndpoint)
			: NetworkEvent(ipEndpoint)
		{}

		EVENT_CLASS_TYPE(ClientConnected)
	};

	class ClientDisconectedEvent : public NetworkEvent
	{
	public:
		ClientDisconectedEvent(IPEndpoint ipEndpoint)
			: NetworkEvent(ipEndpoint)
		{}

		EVENT_CLASS_TYPE(ClientDisconnected)
	};

	/*class ClientPacketEvent : public NetworkEvent
	{
	public:
		ClientPacketEvent(IPEndpoint ipEndpoint, Packet packet)
			: NetworkEvent(ipEndpoint), m_Packet(packet)
		{}

		Packet GetPacket() { return m_Packet; }

		EVENT_CLASS_TYPE(ClientPacket)
	private:
		Packet m_Packet;
	};

	class ServerConnectedEvent : public NetworkEvent
	{
	public:
		ServerConnectedEvent(IPEndpoint ipEndpoint)
			: NetworkEvent(ipEndpoint)
		{}

		EVENT_CLASS_TYPE(ServerConnected)
	};

	class ServerDisconnectedEvent : public NetworkEvent
	{
	public:
		ServerDisconnectedEvent(IPEndpoint ipEndpoint)
			: NetworkEvent(ipEndpoint)
		{}

		EVENT_CLASS_TYPE(ServerDisconnected)
	};

	class ServerPacketEvent : public NetworkEvent
	{
	public:
		ServerPacketEvent(IPEndpoint ipEndpoint, Packet packet)
			: NetworkEvent(ipEndpoint), m_Packet(packet)
		{}

		Packet GetPacket() { return m_Packet; }

		EVENT_CLASS_TYPE(ServerPacket)
	private:
		Packet m_Packet;
	};*/
}