#include "uepch.h"
#include "Network/ServerConnection.h"

#include "Math/Random/Salt.h"

namespace UE
{
	ServerConnection::ServerConnection()
		: Connection()
	{}

	ServerConnection::~ServerConnection()
	{}

	int ServerConnection::Connect()
	{
		switch (m_CurrentConnectionState)
		{
		case Connection::ConnectionState::Disconnected:
		{
			if (m_PacketManager->RemainingReliableIncomingPackets() > 0)
			{
				// Received connection request
				Packet ReceivedPacket = *m_PacketManager->GetReliableIncomingPacket();
				ReceivedPacket >> m_ClientSalt;

				m_CurrentConnectionState = Connection::ConnectionState::SendingChallenge;
			}

			break;
		}
		case Connection::ConnectionState::SendingChallenge:
		{
			// Send challenge packet
			Packet ChallengePacket(PacketType::ConnectionChallengePacket);
			ChallengePacket.SetPacketReliability(true);
			m_ServerSalt = SaltUint64();
			ChallengePacket << m_ClientSalt;
			ChallengePacket << m_ServerSalt;

			SendPacket(CreateRef<Packet>(ChallengePacket));

			m_CurrentConnectionState = Connection::ConnectionState::PendingChallengeResponse;

			break;
		}
		case Connection::ConnectionState::PendingChallengeResponse:
		{
			if (m_PacketManager->RemainingReliableIncomingPackets() > 0)
			{
				// Receive challenge response
				Packet ReceivedPacket = *m_PacketManager->GetReliableIncomingPacket();

				uint64_t ReceivedClientServerSalt = 0;
				ReceivedPacket >> ReceivedClientServerSalt;

				if (ReceivedClientServerSalt == (m_ClientSalt ^ m_ServerSalt))
				{
					m_CurrentConnectionState = Connection::ConnectionState::Connected;

					return 0;
				}
				else
				{
					// STOP CONNECTION ON ERROR AND DENY FOR 5 SECONDS
				}
			}

			break;
		}
		default:
			break;
		}

		return -1;
	}

	int ServerConnection::Disconnect()
	{
		// Send 10 disconnect packets
		return 0;
	}

	int ServerConnection::OnUpdate()
	{
		if ((m_MessageManager->GetReliableOutgoingMessageCount() + m_MessageManager->GetUnreliableOutgoingMessageCount()) <= 0)
		{
			return 0;
		}

		// Create reliable outgoing packet
		if (m_MessageManager->GetReliableOutgoingMessageCount() > 0)
		{
			// Reliable server packet header
			Packet ReliablePacket(PacketType::MessagePacket);

			// Set packet reliability
			ReliablePacket.SetPacketReliability(true);

			// Reliable server packet data
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
		if (m_MessageManager->GetUnreliableOutgoingMessageCount() > 0)
		{
			// Unreliable server packet header
			Packet UnreliablePacket(PacketType::MessagePacket);

			// Set packet reliability
			UnreliablePacket.SetPacketReliability(false);

			// Unreliable server packet data
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