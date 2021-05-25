#pragma once

#include "Network/Message.h"

namespace UE
{
	class MessageManager
	{
	public:

		int Send(Ref<Message> message);

		Ref<Message> GetReliableOutgoingMessage();
		Ref<Message> GetUnreliableOutgoingMessage();

		uint32_t GetReliableOutgoingMessageCount() { return m_ReliableOutgoingMessages.size(); }
		uint32_t GetUnreliableOutgoingMessageCount() { return m_UnreliableOutgoingMessages.size(); }
	private:
		// Outgoing messages
		std::queue<Ref<Message>> m_ReliableOutgoingMessages;
		std::queue<Ref<Message>> m_UnreliableOutgoingMessages;
	};
}