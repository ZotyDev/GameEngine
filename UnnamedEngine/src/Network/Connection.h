#pragma once

#include "Network/IPEndpoint.h"
#include "Network/Packet.h"
#include "Network/MessageManager.h"
#include "Network/PacketManager.h"

// todo: maybe separate Connection into ClientConnection and ServerConnection

namespace UE
{
	class Connection
	{
	public:
		enum ConnectionState
		{
			Disconnected = 0,
			SendingConnectionRequest,
			SendingChallenge,
			PendingChallenge,
			SendingChallengeResponse,
			PendingChallengeResponse,
			Connected
		};
	public:
		Connection();
		~Connection();

		int ClientConnect();
		int ClientDisconnect();

		int ServerConnect();
		int ServerDisconnect();

		bool IsConnected() const { return (m_CurrentConnectionState == Connection::ConnectionState::Connected); }

		Ref<MessageManager> GetMessageManager() { return m_MessageManager; }
		Ref<PacketManager> GetPacketManager() { return m_PacketManager; }

		int SendMessage(Ref<Message> message);
		int SendPacket(Ref<Packet> packet);

		// OnUpdate that should be called from client perspective
		int OnClientUpdate();
		// OnUpdate that should be called from server perspective
		int OnServerUpdate();

		void SetConnectionState(ConnectionState connectionState) { m_CurrentConnectionState = connectionState; }
		ConnectionState GetConnectionState() { return m_CurrentConnectionState; }

		void SetIPEndpoint(IPEndpoint ipEndpoint) { m_IPEndpoint = ipEndpoint; }
		IPEndpoint GetIPEndpoint() { return m_IPEndpoint; }
	private:
		Ref<MessageManager> m_MessageManager;
		Ref<PacketManager> m_PacketManager;
	private:
		ConnectionState m_CurrentConnectionState = ConnectionState::Disconnected;
	private:
		IPEndpoint m_IPEndpoint;
		uint64_t m_ClientSalt = 0;
		uint64_t m_ServerSalt = 0;
		bool m_IsClient = false;
	};
}