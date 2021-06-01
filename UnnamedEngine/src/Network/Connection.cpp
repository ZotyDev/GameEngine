#include "uepch.h"
#include "Network/Connection.h"

#include "Math/Random/Salt.h"

namespace UE
{
	Connection::Connection()
	{
		m_MessageManager = CreateRef<MessageManager>();
		m_PacketManager = CreateRef<PacketManager>();
	}

	Connection::~Connection()
	{}

	int Connection::SendMessage(Ref<Message> message)
	{
		int result = m_MessageManager->Send(message);
		if (result == UE_VALUE_ERROR)
		{
			return -1;
		}

		return 0;
	}

	int Connection::SendPacket(Ref<Packet> packet)
	{
		int result = m_PacketManager->Send(packet);
		if (result == UE_VALUE_ERROR)
		{
			return -1;
		}

		return 0;
	}
}