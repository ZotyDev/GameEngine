#include "uepch.h"
#include "Network/ClientConnection.h"

#include "Math/Random/Salt.h"

namespace UE
{
	ClientConnection::ClientConnection()
		: Connection()
	{}

	ClientConnection::~ClientConnection()
	{}

	int ClientConnection::Connect()
	{
		switch (m_CurrentConnectionState)
		{
		case Connection::ConnectionState::Disconnected:
		{
			// Send connection request
			Packet ConnectionRequest(PacketType::ConnectionRequestPacket);
			ConnectionRequest.SetPacketReliability(true);
			m_ClientSalt = SaltUint64();
			ConnectionRequest << m_ClientSalt;

			SendPacket(CreateRef<Packet>(ConnectionRequest));

			m_CurrentConnectionState = Connection::ConnectionState::PendingChallenge;

			break;
		}
		case Connection::ConnectionState::PendingChallenge:
		{
			if (m_PacketManager->RemainingReliableIncomingPackets() > 0)
			{
				// Received challenge
				Packet ReceivedPacket = *m_PacketManager->GetReliableIncomingPacket();

				uint64_t ReceivedClientSalt = 0;
				uint64_t ReceivedServerSalt = 0;

				ReceivedPacket >> ReceivedClientSalt;
				ReceivedPacket >> ReceivedServerSalt;

				if (ReceivedClientSalt == m_ClientSalt)
				{
					m_ServerSalt = ReceivedServerSalt;
					m_CurrentConnectionState = Connection::ConnectionState::SendingChallengeResponse;
				}
				else
				{
					// STOP CONNECTION ON ERROR AND DENY FOR 5 SECONDS
				}
			}

			break;
		}
		case Connection::ConnectionState::SendingChallengeResponse:
		{
			// Sending challenge response
			Packet ChallengeResponse(PacketType::ConnectionChallengeResponsePacket);
			ChallengeResponse.SetPacketReliability(true);
			ChallengeResponse << (m_ClientSalt ^ m_ServerSalt);

			SendPacket(CreateRef<Packet>(ChallengeResponse));

			m_CurrentConnectionState = Connection::ConnectionState::Connected;

			return 0;
		}
		default:
			break;
		}

		return -1;
	}

	int ClientConnection::Disconnect()
	{
		// Send 10 disconnect packets
		return 0;
	}

	int ClientConnection::OnUpdate()
	{
		if ((m_MessageManager->GetReliableOutgoingMessageCount() + m_MessageManager->GetReliableOutgoingMessageCount()) <= 0)
		{
			return 0;
		}

		// Create reliable outgoing packet
		if (m_MessageManager->GetReliableOutgoingMessageCount() > 0)
		{
			// Reliable packet header
			Packet ReliablePacket(PacketType::MessagePacket);

			// Set reliability
			ReliablePacket.SetPacketReliability(true);

			// Set ClientServer salt
			ReliablePacket << (m_ClientSalt ^ m_ServerSalt);

			// Reliable packet data
			while (m_MessageManager->GetReliableOutgoingMessageCount() > 0)
			{
				ReliablePacket << *m_MessageManager->GetReliableOutgoingMessage();
			}

			// Todo: if packet max size is reached create new packet
			// Todo: implement MaxMessagePerFrame
			// Send may return a error

			// Send completed packet
			m_PacketManager->Send(CreateRef<Packet>(ReliablePacket));
		}

		// Create unreliable outgoing packet
		if (m_MessageManager->GetReliableOutgoingMessageCount() > 0)
		{
			// Unreliable packet header
			Packet UnreliablePacket(PacketType::MessagePacket);

			// Set reliability
			UnreliablePacket.SetPacketReliability(false);

			// Set ClientServer salt
			UnreliablePacket << (m_ClientSalt ^ m_ServerSalt);

			// Unreliable packet data
			while (m_MessageManager->GetUnreliableOutgoingMessageCount() > 0)
			{
				UnreliablePacket << *m_MessageManager->GetUnreliableOutgoingMessage();
			}

			// Todo: if packet max size is reached create new packet
			// Todo: implement MaxMessagePerFrame
			// Send may return a error

			// Send completed packet
			m_PacketManager->Send(CreateRef<Packet>(UnreliablePacket));
		}

		return 0;
	}
}