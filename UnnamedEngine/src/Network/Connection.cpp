#include "uepch.h"
#include "Network/Connection.h"

namespace UE
{
	Connection::Connection()
	{
		m_IPEndpoint = CreateRef<IPEndpoint>();
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
			std::random_device RandomDevice;
			std::mt19937_64 Generator(RandomDevice());
			std::uniform_int_distribution<uint64_t> Distribuition(std::llround(std::pow(2, 62)), std::llround(std::pow(2, 63)));
			m_ClientSalt = Distribuition(Generator);

			Packet ConnectionRequestPacket(Packet::PacketType::ConnectionRequest);
			ConnectionRequestPacket << m_ClientSalt;
			AddOutgoingPacket(CreateRef<Packet>(ConnectionRequestPacket));

			m_CurrentConnectionState = Connection::ConnectionState::PendingChallenge;

			break;
		}
		case Connection::ConnectionState::PendingChallenge:
		{
			// Receive challenge
			Packet ReceivedPacket = *GetIncomingPacket();

			uint64_t ReceivedClientSalt = 0;
			uint64_t ReceivedServerSalt = 0;

			ReceivedPacket >> ReceivedServerSalt;
			ReceivedPacket >> ReceivedClientSalt;

			if (ReceivedClientSalt != m_ClientSalt)
			{
				break;
			}

			m_ServerSalt = ReceivedServerSalt;

			m_CurrentConnectionState = Connection::ConnectionState::SendingChallengeResponse;

			break;
		}
		case Connection::ConnectionState::SendingChallengeResponse:
		{
			// Sending challenge response
			Packet ChallengeResponsePacket(Packet::PacketType::ConnectionChallengeResponse);
			
			uint64_t ClientServerSalt = 0;
			ClientServerSalt = m_ClientSalt ^ m_ServerSalt;

			ChallengeResponsePacket << ClientServerSalt;

			AddOutgoingPacket(CreateRef<Packet>(ChallengeResponsePacket));

			break;
		}
		default:
			break;
		}

		return 0;
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
			// Receive connection request
			Packet ReceivedPacket = *GetIncomingPacket();

			uint64_t ReceivedClientSalt = 0;
			ReceivedPacket >> ReceivedClientSalt;

			m_ClientSalt = ReceivedClientSalt;

			m_CurrentConnectionState = Connection::ConnectionState::SendingChallenge;

			break;
		}
		case Connection::ConnectionState::SendingChallenge:
		{
			// Send challenge packet
			std::random_device RandomDevice;
			std::mt19937_64 Generator(RandomDevice());
			std::uniform_int_distribution<uint64_t> Distribuition(std::llround(std::pow(2, 62)), std::llround(std::pow(2, 63)));
			m_ServerSalt = Distribuition(Generator);

			Packet ChallengePacket(Packet::PacketType::ConnectionChallenge);
			ChallengePacket << m_ClientSalt;
			ChallengePacket << m_ServerSalt;

			m_CurrentConnectionState = Connection::ConnectionState::PendingChallengeResponse;

			break;
		}
		case Connection::ConnectionState::PendingChallengeResponse:
		{
			// Receive challenge response
			Packet ReceivedPacket = *GetIncomingPacket();

			uint64_t ReceivedClientServerSalt = 0;
			ReceivedPacket >> ReceivedClientServerSalt;

			if (ReceivedClientServerSalt != (m_ClientSalt ^ m_ServerSalt))
			{
				break;
			}

			m_CurrentConnectionState = Connection::ConnectionState::Connected;

			break;
		}
		default:
			break;
		}
		return 0;
	}

	int Connection::ServerDisconnect()
	{
		// Fire 10 disconnection packets
		return 0;
	}

	Ref<Packet> Connection::GetIncomingPacket()
	{
		Ref<Packet> t_Packet = m_IncomingPacketQueue.front();
		m_IncomingPacketQueue.pop();
		return t_Packet;
	}

	Ref<Packet> Connection::GetOutgoingPacket()
	{
		Ref<Packet> t_Packet = m_OutgoingPacketQueue.front();
		m_OutgoingPacketQueue.pop();
		return t_Packet;
	}
}