#pragma once

#include "Network/IPEndpoint.h"
#include "Network/Packet.h"

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

		bool IsConnected() const { return m_Connected; }

		void SetConnectionState(ConnectionState connectionState) { m_CurrentConnectionState = connectionState; }
		ConnectionState GetConnectionState() { return m_CurrentConnectionState; }

		Ref<Packet> GetIncomingPacket();
		void AddIncomingPacket(Ref<Packet> incomingPacket) { m_IncomingPacketQueue.push(incomingPacket); }
		uint32_t GetIncomingPacketQueueSize() { return m_IncomingPacketQueue.size(); }

		Ref<Packet> GetOutgoingPacket();
		void AddOutgoingPacket(Ref<Packet> outgoingPacket) { m_OutgoingPacketQueue.push(outgoingPacket); }
		uint32_t GetOutgoingPacketQueueSize() { return m_OutgoingPacketQueue.size(); }

		Ref<IPEndpoint> GetIPEndpoint() { return m_IPEndpoint; }
	private:
		ConnectionState m_CurrentConnectionState = ConnectionState::Disconnected;
	private:
		std::queue<Ref<Packet>> m_IncomingPacketQueue;
		std::queue<Ref<Packet>> m_OutgoingPacketQueue;
		uint64_t m_ClientSalt = 0;
		uint64_t m_ServerSalt = 0;
		Ref<IPEndpoint> m_IPEndpoint;
		bool m_Connected = false;
	};
}