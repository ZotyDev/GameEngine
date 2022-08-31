#pragma once

#include "Network/IPEndpoint.h"

namespace UE
{
	class Connection
	{
	public:
		enum class State
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
		virtual ~Connection();

		virtual UEResult<> Connect() = 0;
		virtual UEResult<> Disconnect() = 0;
		virtual UEResult<> OnUpdate() = 0;
		virtual UEResult<> SendHeartbeat() = 0;

		bool IsConnected() const { return m_CurrentState == Connection::State::Connected; }

	protected:
		Connection::State m_CurrentState = Connection::State::Disconnected;
		IPEndpoint m_IPEndpoint;
		UEUint64 m_ClientSalt = 0;
		UEUint64 m_ServerSalt = 0;
	};
}