#include "uepch.h"
#include "Network/MessageManager.h"

namespace UE
{
	int MessageManager::Send(Ref<Message> message)
	{
		if (message->IsReliable())
		{
			m_ReliableOutgoingMessages.push(message);
		}
		else
		{
			m_UnreliableOutgoingMessages.push(message);
		}

		return 0;
	}

	Ref<Message> MessageManager::GetReliableOutgoingMessage()
	{
		if (!m_ReliableOutgoingMessages.empty())
		{
			Ref<Message> t_MessagePtr = m_ReliableOutgoingMessages.front();
			m_ReliableOutgoingMessages.pop();
			return t_MessagePtr;
		}

		return nullptr;
	}

	Ref<Message> MessageManager::GetUnreliableOutgoingMessage()
	{
		if (!m_UnreliableOutgoingMessages.empty())
		{
			Ref<Message> t_MessagePtr = m_UnreliableOutgoingMessages.front();
			m_UnreliableOutgoingMessages.pop();
			return t_MessagePtr;
		}

		return nullptr;
	}
}