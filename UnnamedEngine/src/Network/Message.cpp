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

	void Append(std::vector<char>* target, const void* data, UEUint32 size)
	{
		if ((target->size() + size) > MESSAGE_ARRAY_MAX_SIZE)
		{
			UE_CORE_ERROR("Message size exceeds max");
			return;
		}

		target->insert(target->end(), (char*)data, (char*)data + size);
	}

	Message& Message::operator<<(bool data)
	{
		// put value inside packer
		if (m_PackerIndex + 1 > 63)
		{
			
		}
		else
		{

		}

		// if compressor is full, write value to buffer

		return *this;
	}

	Message& Message::operator>>(bool& data)
	{
		// put required info inside unpacker

		return *this;
	}
}