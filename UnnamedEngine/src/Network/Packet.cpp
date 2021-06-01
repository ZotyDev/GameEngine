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
		PacketType* packetTypePtr = reinterpret_cast<PacketType*>(&m_Buffer[1]);
		*packetTypePtr = static_cast<PacketType>(UE_UINT16_HTON(packetType));
	}

	Packet::PacketType Packet::GetPacketType()
	{
		PacketType* packetTypePtr = reinterpret_cast<PacketType*>(&m_Buffer[1]);
		return static_cast<PacketType>(UE_UINT16_NTOH(*packetTypePtr));
	}

	void Packet::SetPacketReliability(bool isReliable)
	{
		bool* packetReliabilityPtr = reinterpret_cast<bool*>(&m_Buffer[0]);
		*packetReliabilityPtr = static_cast<bool>(isReliable);
	}

	bool Packet::IsReliable()
	{
		bool* packetReliabilityPtr = reinterpret_cast<bool*>(&m_Buffer[0]);
		return static_cast<bool>(*packetReliabilityPtr);
	}

	void Packet::Clear()
	{
		m_Buffer.resize(sizeof(bool) + sizeof(PacketType));
		SetPacketType(PacketType::Invalid);
		m_ExtractionOffset = sizeof(bool) + sizeof(PacketType);
	}

	void Packet::Append(const void* data, uint32_t size)
	{
		if ((m_Buffer.size() + size) > UE_MAX_PACKET_SIZE)
		{
			UE_CORE_ERROR("Packet size exceeds max packet size");
			return;
		}

		m_Buffer.insert(m_Buffer.end(), (char*)data, (char*)data + size);
	}

	Packet& Packet::operator<<(uint16_t data)
	{
		data = UE_UINT16_HTON(data);
		Append(&data, sizeof(uint16_t));
		return *this;
	}

	Packet& Packet::operator>>(uint16_t& data)
	{
		if ((m_ExtractionOffset + sizeof(uint16_t)) > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size");
		}

		data = *reinterpret_cast<uint16_t*>(&m_Buffer[m_ExtractionOffset]);
		data = UE_UINT16_NTOH(data);
		m_ExtractionOffset += sizeof(uint16_t);
		return *this;
	}

	Packet& Packet::operator<<(uint32_t data)
	{
		data = UE_UINT32_HTON(data);
		Append(&data, sizeof(uint32_t));
		return *this;
	}

	Packet& Packet::operator>>(uint32_t& data)
	{
		if ((m_ExtractionOffset + sizeof(uint32_t)) > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size");
		}

		data = *reinterpret_cast<uint32_t*>(&m_Buffer[m_ExtractionOffset]);
		data = UE_UINT32_NTOH(data);
		m_ExtractionOffset += sizeof(uint32_t);
		return *this;
	}

	Packet& Packet::operator<<(uint64_t data)
	{
		data = UE_UINT64_HTON(data);
		Append(&data, sizeof(uint64_t));
		return *this;
	}

	Packet& Packet::operator>>(uint64_t& data)
	{
		if ((m_ExtractionOffset + sizeof(uint64_t)) > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size");
		}

		data = *reinterpret_cast<uint64_t*>(&m_Buffer[m_ExtractionOffset]);
		data = UE_UINT64_NTOH(data);
		m_ExtractionOffset += sizeof(uint64_t);
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

		uint32_t StringSize = 0;
		*this >> StringSize;

		if ((m_ExtractionOffset + StringSize) > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size");
		}

		data.resize(StringSize);
		data.assign(&m_Buffer[m_ExtractionOffset], StringSize);
		m_ExtractionOffset += StringSize;
		return *this;
	}

	Packet& Packet::operator<<(Message& data)
	{
		*this << (uint32_t)data.GetMessageSize();
		Append(data.GetBuffer().data(), data.GetMessageSize());
		return *this;
	}

	Packet& Packet::operator>>(Message& data)
	{
		data.Clear();

		uint32_t MessageSize = 0;
		*this >> MessageSize;

		if ((m_ExtractionOffset + MessageSize) > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size bro wtf");
		}

		std::string DataReader;
		DataReader.resize(MessageSize);
		DataReader.assign(&m_Buffer[m_ExtractionOffset], MessageSize);
		m_ExtractionOffset += MessageSize;

		data.SetBuffer({ DataReader.begin(), DataReader.end() });

		return *this;
	}
}