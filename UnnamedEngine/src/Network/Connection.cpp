#include "uepch.h"
#include "Network/Connection.h"

#include "Math/Random/Salt.h"

namespace UE
{
	Connection::Connection()
	{
		m_MessageManager = CreateRef<MessageManager>();
		m_PacketManager = CreateRef<PacketManager>();
	}

	Connection::~Connection()
	{
	}

	int Connection::ClientConnect()
	{
		switch (m_CurrentConnectionState)
		{
		case Connection::ConnectionState::Disconnected:
		{
			// Send connection request
			Packet ConnectionRequest(Packet::PacketType::ConnectionRequest);
			ConnectionRequest.SetPacketReliability(true);
			m_ClientSalt = SaltUint64();
			ConnectionRequest << m_ClientSalt;

			SendPacket(CreateRef<Packet>(ConnectionRequest));

			m_CurrentConnectionState = Connection::ConnectionState::PendingChallenge;

			UE_CORE_INFO("Connecting to {0}", m_IPEndpoint.GetAddress());

			break;
		}
		case Connection::ConnectionState::PendingChallenge:
		{
			if (m_PacketManager->RemainingReliableIncomingPackets() > 0)
			{
				// Receive challenge
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
			Packet ChallengeResponse(Packet::PacketType::ConnectionChallengeResponse);
			ChallengeResponse.SetPacketReliability(true);
			ChallengeResponse << (m_ClientSalt ^ m_ServerSalt);

			SendPacket(CreateRef<Packet>(ChallengeResponse));

			m_CurrentConnectionState = Connection::ConnectionState::Connected;

			UE_CORE_INFO("Connected to {0}", m_IPEndpoint.GetAddress());

			return 0;
		}
		default:
			break;
		}

		return -1;
	}

	int Connection::ClientDisconnect()
	{
		// Fire 10 disconnection packets
		return 0;
	}

	int Connection::ServerConnect()
	{
		switch (m_CurrentConnectionState)
		{
		case Connection::ConnectionState::Disconnected:
		{
			if (m_PacketManager->RemainingReliableIncomingPackets() > 0)
			{
				// Receive connection request
				Packet ReceivedPacket = *m_PacketManager->GetReliableIncomingPacket();
				ReceivedPacket >> m_ClientSalt;

				m_CurrentConnectionState = Connection::ConnectionState::SendingChallenge;
			}

			UE_CORE_INFO("Receiving connection request from {0}", m_IPEndpoint.GetAddress());

			break;
		}
		case Connection::ConnectionState::SendingChallenge:
		{
			// Send challenge packet
			Packet ChallengePacket(Packet::PacketType::ConnectionChallenge);
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
					
					UE_CORE_INFO("Accepted connection from {0}", m_IPEndpoint.GetAddress());
					
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

	int Connection::ServerDisconnect()
	{
		// Fire 10 disconnection packets
		return 0;
	}

	int Connection::SendMessage(Ref<Message> message)
	{
		int result = m_MessageManager->Send(message);
		if (result == UE_VALUE_ERROR)
		{
			return -1;
		}

		return 0;
	}

	int Connection::SendPacket(Ref<Packet> packet)
	{
		int result = m_PacketManager->Send(packet);
		if (result == UE_VALUE_ERROR)
		{
			return -1;
		}

		return 0;
	}

	int Connection::OnClientUpdate()
	{
		if ((m_MessageManager->GetReliableOutgoingMessageCount() + m_MessageManager->GetUnreliableOutgoingMessageCount()) <= 0)
		{
			return 0;
		}

		// Create reliable outgoing packet
		if (m_MessageManager->GetReliableOutgoingMessageCount() > 0)
		{
			// Reliable client packet header 
			Packet ReliablePacket(Packet::PacketType::MessagePacket);
			ReliablePacket.SetPacketReliability(true);
			ReliablePacket << (m_ClientSalt ^ m_ServerSalt);

			// Reliable client packet data
			while (m_MessageManager->GetReliableOutgoingMessageCount() > 0)
			{
				ReliablePacket << *m_MessageManager->GetReliableOutgoingMessage();
			}

			// Todo: if packet max size is reached create new packet
			// Send may return a error

			// "Send" completed packet
			m_PacketManager->Send(CreateRef<Packet>(ReliablePacket));
		}

		// Create unreliable outgoing packet
		if (m_MessageManager->GetUnreliableOutgoingMessageCount() > 0)
		{
			// Unreliable client packet header
			Packet UnreliablePacket(Packet::PacketType::MessagePacket);
			UnreliablePacket.SetPacketReliability(false);
			UnreliablePacket << (m_ClientSalt ^ m_ServerSalt);

			// Unreliable client packet data
			while (m_MessageManager->GetUnreliableOutgoingMessageCount() > 0)
			{
				UnreliablePacket << *m_MessageManager->GetUnreliableOutgoingMessage();
			}

			// Todo: if packet max size is reached create new packet
			// Send may return a error

			// "Send" completed packet
			m_PacketManager->Send(CreateRef<Packet>(UnreliablePacket));
		}

		return 0;
	}

	int Connection::OnServerUpdate()
	{
		if ((m_MessageManager->GetReliableOutgoingMessageCount() + m_MessageManager->GetUnreliableOutgoingMessageCount()) <= 0)
		{
			return 0;
		}

		// Create reliable outgoing packet
		if (m_MessageManager->GetReliableOutgoingMessageCount() > 0)
		{
			// Reliable server packet header
			Packet ReliablePacket(Packet::PacketType::MessagePacket);
			ReliablePacket.SetPacketReliability(true);

			// Reliable server packet data
			while (m_MessageManager->GetReliableOutgoingMessageCount() > 0)
			{
				ReliablePacket << *m_MessageManager->GetReliableOutgoingMessage();
			}

			// Todo: if packet max size is reached create new packet

			// "Send" completed packet
			m_PacketManager->Send(CreateRef<Packet>(ReliablePacket));
		}

		// Create unreliable outgoing packet
		if (m_MessageManager->GetUnreliableOutgoingMessageCount() > 0)
		{
			// Unreliable server packet header
			Packet UnreliablePacket(Packet::PacketType::MessagePacket);
			UnreliablePacket.SetPacketReliability(false);

			// Unreliable server packet data
			while (m_MessageManager->GetUnreliableOutgoingMessageCount() > 0)
			{
				UnreliablePacket << *m_MessageManager->GetUnreliableOutgoingMessage();
			}

			// Todo: if packet max size is reached create new packet

			// "Send" completed packet
			m_PacketManager->Send(CreateRef<Packet>(UnreliablePacket));
		}

		return 0;
	}
}