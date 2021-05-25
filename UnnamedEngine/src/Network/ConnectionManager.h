#pragma once

#include "Core/Base.h"
#include "Network/NetworkAPI.h"
#include "Network/Socket.h"
#include "Network/Connection.h"

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
		std::unordered_map<IPEndpoint, Ref<Connection>>& GetConnections() { return m_Connections; }
		std::list<Ref<Connection>>& GetConnectionsReceivingPackets() { return m_ConnectionsReceivingPackets; }
		std::list<Ref<Connection>>& GetConnectionsReceivingErrors() { return m_ConnectionsReceivingErrors; }
		std::list<Ref<Connection>>& GetConnectionsStarting() { return m_ConnectionsStarting; }
	private:
		Ref<Socket> m_ListeningSocket;
		std::unordered_map<IPEndpoint, Ref<Connection>> m_Connections;
		std::list<Ref<Connection>> m_ConnectionsReceivingPackets;
		std::list<Ref<Connection>> m_ConnectionsReceivingErrors;
		std::list<Ref<Connection>> m_ConnectionsStarting;
	};
}