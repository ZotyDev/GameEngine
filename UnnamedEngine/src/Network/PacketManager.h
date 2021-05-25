#pragma once

#include "Network/Packet.h"

namespace UE
{
	class PacketManager
	{
	public:

		int Send(Ref<Packet> packet);
		int Receive(Ref<Packet> packet);

		uint32_t RemainingReliableOutgoingPackets() { return m_ReliableOutgoingPackets.size(); }
		uint32_t RemainingUnreliableOutgoingPackets() { return m_UnreliableOutgoingPackets.size(); }

		uint32_t RemainingReliableIncomingPackets() { return m_ReliableIncomingPackets.size(); }
		uint32_t RemainingUnreliableIncomingPackets() { return m_UnreliableIncomingPackets.size(); }

		Ref<Packet> GetReliableOutgoingPacket();
		Ref<Packet> GetUnreliableOutgoingPacket();

		Ref<Packet> GetReliableIncomingPacket();
		Ref<Packet> GetUnreliableIncomingPacket();
	private:
		// Outgoing packets
		std::queue<Ref<Packet>> m_ReliableOutgoingPackets;
		std::queue<Ref<Packet>> m_UnreliableOutgoingPackets;

		// Incoming packets
		std::queue<Ref<Packet>> m_ReliableIncomingPackets;
		std::queue<Ref<Packet>> m_UnreliableIncomingPackets;
	};
}