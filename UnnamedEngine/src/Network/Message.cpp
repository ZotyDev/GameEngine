#include "uepch.h"
#include "Network/Message.h"

namespace UE
{
	MessageLayout::MessageLayout(UEUint32 size)
	{
		m_Elements.resize(size);
	}

	UEResult MessageLayoutLibrary::RegisterMessageLayout(const std::string& name, Ref<MessageLayout> messageLayout)
	{
		auto it = m_MessageLayouts.find(name);
		if (it == m_MessageLayouts.end())
		{
			UE_CORE_ERROR("Failed to register message layout: name already registered");
			return UEResult::Error;
		}

		m_MessageLayouts.insert({ name, messageLayout });

		return UEResult::Success;
	}

	UEResult MessageLayoutLibrary::LoadMessageLayout(const std::string& name, Ref<MessageLayout> messageLayout)
	{
		auto it = m_MessageLayouts.find(name);
		if (it != m_MessageLayouts.end())
		{
			UE_CORE_ERROR("Failed to load message layout: name not registered");
			return UEResult::Error;
		}

		messageLayout = it->second;

		return UEResult::Success;
	}

	Message::Message(Ref<MessageLayout> layout)
		: m_Layout(layout)
	{}

	Message& Message::operator<<(bool data)
	{


		return *this;
	}

	Message& Message::operator>>(bool& data)
	{
		return *this;
	}
}