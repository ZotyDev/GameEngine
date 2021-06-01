#include "uepch.h"
#include "Network/PacketManager.h"

namespace UE
{
	int PacketManager::Send(Ref<Packet> packet)
	{
		if (packet->IsReliable())
		{
			m_ReliableOutgoingPackets.push(packet);
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
			m_ReliableOutgoingPackets.pop();
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
			m_ReliableIncomingPackets.pop();
			return t_PacketPtr;
		}

		return nullptr;
	}
}