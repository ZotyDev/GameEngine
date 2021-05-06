#pragma once

#define UE_MAX_PACKET_SIZE 8192

namespace UE
{
	class Packet
	{
	public:
		enum PacketType : uint16_t
		{
			Invalid,
			UIntArray,
			UShortArray,
			ULongArray,
			ULongLongArray,
			CharArray,
			UCharArray,
			BoolArray,
			FloatArray,
			DoubleArray,
			RawByteArray
		};
	public:
		enum PacketTask
		{
			ProcessPacketSize,
			ProcessPacketContents
		};
	public:
		Packet(PacketType packetType = PacketType::Invalid);

		void SetPacketType(const PacketType& packetType);
		PacketType GetPacketType();

		void Clear();
		void Append(const void* data, uint32_t size);

		Packet& operator << (uint32_t data);
		Packet& operator >> (uint32_t& data);

		Packet& operator << (const std::string& data);
		Packet& operator >> (std::string& data);

		uint32_t m_ExtractionOffset;
		std::vector<char> m_Buffer;
	};
}