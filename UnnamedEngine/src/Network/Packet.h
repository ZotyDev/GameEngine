#pragma once

#define UE_MAX_PACKET_SIZE 1024

#include "Network/Message.h"

namespace UE
{
	class Packet
	{
	public:
		enum PacketType : uint16_t
		{
			First,

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
			RawByteArray,

			MessagePacket,

			ConnectionRequest,
			ConnectionChallenge,
			ConnectionChallengeResponse,

			Last
		};
	public:
		Packet(PacketType packetType = PacketType::Invalid);

		void SetPacketType(const PacketType& packetType);
		PacketType GetPacketType();
		void SetPacketReliability(bool isReliable);
		bool IsReliable();

		void Clear();
		void Append(const void* data, uint32_t size);

		Packet& operator << (uint32_t data);
		Packet& operator >> (uint32_t& data);

		Packet& operator << (uint64_t data);
		Packet& operator >> (uint64_t& data);

		Packet& operator << (const std::string& data);
		Packet& operator >> (std::string& data);

		Packet& operator << (Message& data);
		Packet& operator >> (Message& data);

		uint64_t m_ExtractionOffset;
		std::vector<char> m_Buffer;
	};
}