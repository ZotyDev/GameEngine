#pragma once

#include "Events/Event.h"
#include "Network/Packet.h"

namespace UE
{
	class NetworkEvent : public Event
	{
	public:
		std::string GetIp() const { return m_IP; }
		unsigned int GetPort() const { return m_Port; }
		std::string GetAddress() const { return m_IP + ":" + std::to_string(m_Port); }

		EVENT_CLASS_CATEGORY(EventCategoryNetwork)
	protected:
		NetworkEvent(std::string ip, unsigned short port)
			: m_IP(ip), m_Port(port)
		{
		}

		std::string m_IP;
		unsigned short m_Port;
	};

	class ClientConnectedEvent : public NetworkEvent
	{
	public:
		ClientConnectedEvent(std::string ip, unsigned short port)
			: NetworkEvent(ip, port)
		{}

		EVENT_CLASS_TYPE(ClientConnected)
	};

	class ClientDisconectedEvent : public NetworkEvent
	{
	public:
		ClientDisconectedEvent(std::string ip, unsigned short port)
			: NetworkEvent(ip, port)
		{}

		EVENT_CLASS_TYPE(ClientDisconnected)
	};

	class ClientMessageEvent : public NetworkEvent
	{
	public:
		ClientMessageEvent(std::string ip, unsigned short port, Ref<Packet> packet)
			: NetworkEvent(ip, port), m_Packet(packet)
		{}

		Ref<Packet> GetPacket() { return m_Packet; }

		EVENT_CLASS_TYPE(ClientMessage)
	private:
		Ref<Packet> m_Packet;
	};
}