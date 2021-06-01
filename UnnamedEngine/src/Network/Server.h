#pragma once

#include "Network/NetworkAPI.h"
#include "Network/Socket.h"
#include "Network/ClientConnection.h"
#include "Network/ServerConnection.h"
#include "Network/ConnectionManager.h"
#include "Events/Event.h"

namespace UE
{
	class Server
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		Server();
		~Server();

		void Init(std::string port);
		void Shutdown();

		void OnUpdate();

		int SendMessage(Ref<Message> message);

		void SetEventCallback(const EventCallbackFn& callback)
		{
			m_EventCallbackFn = callback;
		};

		uint32_t GetConnectionCount() const { return m_ConnectionCount; }
		uint32_t GetMaxConnections() const { return m_MaxConnections; }
		void SetMaxConnections(uint32_t maxConnections) { m_MaxConnections = maxConnections; }

	private:
		EventCallbackFn m_EventCallbackFn;
	private:
		Ref<Socket> m_ListeningSocket;
		Ref<ClientConnection> m_ListeningConnection;
		
		ConnectionManager m_ConnectionManager;

		uint32_t m_ConnectionCount = 0;
		uint32_t m_MaxConnections = 16; 
	};
}