#pragma once

#include "Network/NetworkAPI.h"

#define MAX_MESSAGE_SIZE 1024
#define MESSAGE_ARRAY_MAX_SIZE MAX_MESSAGE_SIZE / 64

namespace UE
{
	struct MessageLayout
	{
		MessageLayout(UEUint32 size);
		std::vector<UEVValue> m_Elements;
	};

	class MessageLayoutLibrary
	{
	public:
		UEResult RegisterMessageLayout(const std::string& name, Ref<MessageLayout> messageLayout);
		UEResult LoadMessageLayout(const std::string& name, Ref<MessageLayout> messageLayout);

	private:
		std::unordered_map<std::string, Ref<MessageLayout>> m_MessageLayouts;
	};

	class Message
	{
	public:
		Message() = default;
		Message(Ref<MessageLayout> layout);

		Message& operator << (bool data);
		Message& operator >> (bool& data);

	private:
		Ref<MessageLayout> m_Layout;

	private:
		UEUint64 m_Packer = 0;
		UEUint8 m_PackerIndex = 0;

		//UEUint64* m_Buffer;
	};
}