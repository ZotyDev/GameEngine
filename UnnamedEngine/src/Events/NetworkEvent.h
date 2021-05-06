#pragma once

#include "Events/Event.h"

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
		ClientMessageEvent(std::string ip, unsigned short port, const char* data)
			: NetworkEvent(ip, port), m_Data(data)
		{}

		const char* GetData() { return m_Data; }

		EVENT_CLASS_TYPE(ClientMessage)
	private:
		const char* m_Data;
	};
}