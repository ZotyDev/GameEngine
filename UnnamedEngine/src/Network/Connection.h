#pragma once

#include "Network/Socket.h"
#include "Network/Packet.h"

namespace UE
{
	class Connection
	{
	public:
		Connection(Ref<Socket> socket);
		void Close();

		Ref<Socket> m_Socket;

		Packet::PacketTask m_Task = Packet::PacketTask::ProcessPacketSize;
		int m_ExtractionOffset = 0;
		uint16_t m_PacketSize = 0;
		char m_Buffer[UE_MAX_PACKET_SIZE];
	};
}