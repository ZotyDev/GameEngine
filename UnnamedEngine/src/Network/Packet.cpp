#include "uepch.h"
#include "Network/Packet.h"

namespace UE
{
	Packet::Packet(PacketType packetType)
	{
		Clear();
		SetPacketType(packetType);
	};

	void Packet::SetPacketType(const PacketType& packetType)
	{
		PacketType* packetTypePtr = reinterpret_cast<PacketType*>(&m_Buffer[0]);
		*packetTypePtr = static_cast<PacketType>(UE_HTONS(packetType));
	}

	Packet::PacketType Packet::GetPacketType()
	{
		PacketType* packetTypePtr = reinterpret_cast<PacketType*>(&m_Buffer[0]);
		return static_cast<PacketType>(UE_NTOHS(*packetTypePtr));
	}

	void Packet::Clear()
	{
		m_Buffer.resize(sizeof(PacketType));
		SetPacketType(PacketType::Invalid);
		m_ExtractionOffset = sizeof(PacketType);
	}

	void Packet::Append(const void* data, uint32_t size)
	{
		if ((m_Buffer.size() + size) > UE_MAX_PACKET_SIZE)
		{
			UE_CORE_ERROR("Packet size exceeds max packet size!");
			return;
		}

		m_Buffer.insert(m_Buffer.end(), (char*)data, (char*)data + size);
	}

	Packet& Packet::operator<<(uint32_t data)
	{
		data = UE_HTONL(data);
		Append(&data, sizeof(uint32_t));
		return *this;
	}

	Packet& Packet::operator>>(uint32_t& data)
	{
		if ((m_ExtractionOffset + sizeof(uint32_t)) > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction ofsset exceeded buffer size!");
		}

		data = *reinterpret_cast<uint32_t*>(&m_Buffer[m_ExtractionOffset]);
		data = UE_NTOHL(data);
		m_ExtractionOffset += sizeof(uint32_t);
		return *this;
	}

	Packet& Packet::operator<<(const std::string& data)
	{
		*this << (uint32_t)data.size();
		Append(data.data(), data.size());
		return *this;
	}

	Packet& Packet::operator>>(std::string& data)
	{
		data.clear();

		uint32_t t_StringSize = 0;
		*this >> t_StringSize;

		if ((m_ExtractionOffset + t_StringSize) > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction ofsset exceeded buffer size!");
		}

		data.resize(t_StringSize);
		data.assign(&m_Buffer[m_ExtractionOffset], t_StringSize);
		m_ExtractionOffset += t_StringSize;
		return *this;
	}
}