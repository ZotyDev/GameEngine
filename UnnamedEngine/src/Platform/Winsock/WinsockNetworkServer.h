#pragma once

#include "Network/NetworkServer.h"
#include "Network/Socket.h"
#include "Network/Packet.h"
#include "Network/Connection.h"

#include <winsock2.h>
#include <WS2tcpip.h>

namespace UE
{
	class WinsockNetworkServer : public NetworkServer
	{
	public:
		WinsockNetworkServer() = default;
		virtual ~WinsockNetworkServer() override;

		virtual void Init(std::string port) override;
		virtual void Shutdown() override;

		virtual void OnUpdate() override;

		virtual void SetEventCallback(const EventCallbackFn& callback) override { m_EventCallbackFn = callback; };
	private:
		void CloseConnection(int socketIndex);
		bool ProcessPacket(Packet& packet);
	private:
		EventCallbackFn m_EventCallbackFn;

		Ref<Socket> m_ListeningSocket;
		std::vector<Connection> m_Connections;
		int m_ConnectionIndex = 0;

		std::vector<WSAPOLLFD> m_MasterFD;
		std::vector<WSAPOLLFD> m_UseFD;
	};
}