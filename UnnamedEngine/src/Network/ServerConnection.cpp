#include "uepch.h"
#include "Network/ServerConnection.h"

namespace UE
{
	ServerConnection::ServerConnection()
	{}

	ServerConnection::~ServerConnection()
	{}

	UEResult<> ServerConnection::Connect()
	{
		switch (m_CurrentState)
		{
			case UE::Connection::State::Disconnected:
			{
				// Receive connection request

				break;
			}
			case UE::Connection::State::SendingChallenge:
			{
				// Send challenge

				break;
			}
			case UE::Connection::State::PendingChallengeResponse:
			{
				// Receive challenge response

				// Validate challenge response

				break;
			}
		}

		return UEResult<>::Success;
	}

	UEResult<> ServerConnection::Disconnect()
	{
		// Send 10 disconnect

		return UEResult<>::Success;
	}

	UEResult<> ServerConnection::OnUpdate()
	{
		return UEResult<>::Success;
	}

	UEResult<> ServerConnection::SendHeartbeat()
	{
		return UEResult<>::Success;
	}
}