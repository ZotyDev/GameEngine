#pragma once

#define UE_MAX_PACKET_SIZE 1024

#include "Network/Message.h"

namespace UE
{
	enum PacketProtocol : uint8_t
	{
		InvalidProtocol,
		UEUDP
	};

	enum PacketType : uint16_t
	{
		FirstPacket,

		InvalidPacket,

		MessagePacket,

		ConnectionRequestPacket,
		ConnectionChallengePacket,
		ConnectionChallengeResponsePacket,

		ConnectionFirstPacket = ConnectionRequestPacket,
		ConnectionLastPacket = ConnectionChallengeResponsePacket,

		LastPacket
	};

	class Packet
	{
	public:
		Packet(PacketType packetType = PacketType::InvalidPacket);

		void SetPacketProtocol(const PacketProtocol& packetProtocol);
		PacketProtocol GetPacketProtocol();
		void SetPacketReliability(bool isReliable);
		bool IsReliable();
		void SetPacketType(const PacketType& packetType);
		PacketType GetPacketType();

		bool IsChecksum(uint32_t checksum);
		bool IsGreaterEqualToChecksum(uint32_t checksum);

		void Clear();
		void Append(const void* data, uint32_t size);

		Packet& operator << (uint16_t data);
		Packet& operator >> (uint16_t& data);

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