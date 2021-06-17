#include "uepch.h"
#include "Network/PacketManager.h"

namespace UE
{
	int PacketManager::Send(Ref<Packet> packet)
	{
		if (packet->IsReliable())
		{
			unsigned long long PacketInsertPosition = m_ReliableOutgoingPackets.size();
			
			m_ReliableOutgoingPackets.push_back(packet);

			// Get the current packet sequence
			uint16_t* PacketSequencePtr = reinterpret_cast<uint16_t*>(&packet->m_Buffer[12]);
			uint16_t PacketSequence = static_cast<uint16_t>(*PacketSequencePtr);
			PacketSequence = UE_NTOHS(PacketSequence);

			// Check if there is already a packet with this sequence
			if (m_SequencePacketMap.find(PacketSequence) != m_SequencePacketMap.end())
			{
				// Todo: Packet was dropped, notify something somewhere
			}

			// Register vector position using sequence as index
			m_SequencePacketMap.insert({ PacketSequence, PacketInsertPosition });
		}
		else
		{
			m_UnreliableOutgoingPackets.push(packet);
		}

		return 0;
	}

	int PacketManager::Receive(Ref<Packet> packet)
	{
		if (packet->IsReliable())
		{
			// Extract the sequence
			uint16_t ReceivedSequence = 0;
			*packet >> ReceivedSequence;

			if (ReceivedSequence > m_LastSequenceReceived)
			{
				m_LastSequenceReceived = ReceivedSequence;
			}

			// Extract the ACK
			uint16_t ReceivedACK = 0;
			*packet >> ReceivedACK;

			// Extract the ACKBits
			uint32_t ReceivedACKBits = 0;
			*packet >> ReceivedACKBits;

			// Remove ACKED packets
			std::bitset<32> ACKBitsBitset(ReceivedACKBits);
			for (int i = 0; i < 32; i++)
			{
				// Check if bit in position i is set to 1
				if (ACKBitsBitset.test(i))
				{
					// Check if packet is unACKED
					if (m_SequencePacketMap.find(ReceivedACK - i) != m_SequencePacketMap.end())
					{
						// Remove packet ACK - i from outgoing list
						m_SequencePacketMap.erase(ReceivedSequence - i);
					}
					else
					{
						UE_CORE_ERROR("Received ACK for already ACKed packet: Received {0}", ReceivedACK - i);
					}
				}
			}

			m_ReliableIncomingPackets.push(packet);
		}
		else
		{
			m_UnreliableIncomingPackets.push(packet);
		}

		return 0;
	}

	Ref<Packet> PacketManager::GetReliableOutgoingPacket()
	{
		if (!m_ReliableOutgoingPackets.empty())
		{
			Ref<Packet> t_PacketPtr = m_ReliableOutgoingPackets.front();
			m_ReliableOutgoingPackets.erase(m_ReliableOutgoingPackets.begin());
			return t_PacketPtr;
		}

		return nullptr;
	}

	Ref<Packet> PacketManager::GetUnreliableOutgoingPacket()
	{
		if (!m_UnreliableOutgoingPackets.empty())
		{
			Ref<Packet> t_PacketPtr = m_UnreliableOutgoingPackets.front();
			m_UnreliableOutgoingPackets.pop();
			return t_PacketPtr;
		}

		return nullptr;
	}

	Ref<Packet> PacketManager::GetReliableIncomingPacket()
	{
		if (!m_ReliableIncomingPackets.empty())
		{
			Ref<Packet> t_PacketPtr = m_ReliableIncomingPackets.front();
			m_ReliableIncomingPackets.pop();
			return t_PacketPtr;
		}

		return nullptr;
	}

	Ref<Packet> PacketManager::GetUnreliableIncomingPacket()
	{
		if (!m_UnreliableIncomingPackets.empty())
		{
			Ref<Packet> t_PacketPtr = m_UnreliableIncomingPackets.front();
			m_UnreliableIncomingPackets.pop();
			return t_PacketPtr;
		}

		return nullptr;
	}
}