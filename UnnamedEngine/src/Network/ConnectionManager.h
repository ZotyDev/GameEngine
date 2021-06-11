#pragma once

#include "Core/Base.h"
#include "Network/NetworkAPI.h"
#include "Network/Socket.h"
#include "Network/ServerConnection.h"

// Todo: change std::list to std::queue

namespace UE
{
	class ConnectionManager
	{
	public:
		ConnectionManager();
		~ConnectionManager();

		int Init(Ref<Socket> listeningSocket);
		int Poll();
		Ref<Socket> GetListeningConnection() const { return m_ListeningSocket; }
		std::unordered_map<IPEndpoint, Ref<ServerConnection>>& GetConnections() { return m_Connections; }
		std::list<Ref<ServerConnection>>& GetConnectionsReceivingPackets() { return m_ConnectionsReceivingPackets; }
		std::list<Ref<ServerConnection>>& GetConnectionsReceivingErrors() { return m_ConnectionsReceivingErrors; }
		std::list<Ref<ServerConnection>>& GetConnectionsConnecting() { return m_ConnectionsConnecting; }
	private:
		Ref<Socket> m_ListeningSocket;
		std::unordered_map<IPEndpoint, Ref<ServerConnection>> m_Connections;
		std::list<Ref<ServerConnection>> m_ConnectionsReceivingPackets;
		std::list<Ref<ServerConnection>> m_ConnectionsReceivingErrors;
		std::list<Ref<ServerConnection>> m_ConnectionsConnecting;
	};
}