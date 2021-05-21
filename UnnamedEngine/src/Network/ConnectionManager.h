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
		ConnectionManager() = default;
		virtual ~ConnectionManager() = default;

		virtual int Init(Ref<Socket> listeningSocket) = 0;
		virtual int Poll() = 0;
		Ref<Socket> GetListeningConnection() const { return m_ListeningSocket; }
		std::unordered_map<IPEndpoint, Ref<Connection>>& GetConnections() { return m_Connections; }
		std::list<Ref<Connection>>& GetConnectionsReceivingPackets() { return m_ConnectionsReceivingPackets; }
		std::list<Ref<Connection>>& GetConnectionsReceivingErrors() { return m_ConnectionsReceivingErrors; }
		std::list<Ref<Connection>>& GetConnectionsStarting() { return m_ConnectionsStarting; }

		static Scope<ConnectionManager> Create();
	protected:
		Ref<Socket> m_ListeningSocket;
		std::unordered_map<IPEndpoint, Ref<Connection>> m_Connections;
		std::list<Ref<Connection>> m_ConnectionsReceivingPackets;
		std::list<Ref<Connection>> m_ConnectionsReceivingErrors;
		std::list<Ref<Connection>> m_ConnectionsStarting;
	};
}