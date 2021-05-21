#pragma once

#include "Network/NetworkAPI.h"
#include "Network/Socket.h"
#include "Network/Connection.h"
#include "Events/Event.h"

namespace UE
{
	class Client
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		Client();
		~Client();

		void Init();
		void Shutdown();

		void OnUpdate();

		int Connect(IPEndpoint destination);

		bool IsConnected() { return m_Connected; }

		void SetEventCallback(const EventCallbackFn& callback)
		{
			m_EventCallbackFn = callback;
		};

	private:
		EventCallbackFn m_EventCallbackFn;
	private:
		Ref<Socket> m_Socket;
		Ref<Connection> m_Connection;
		bool m_AttemptingConnection = false;
		bool m_Connected = false;
	};
}