#include "uepch.h"
#include "Network/Message.h"

namespace UE
{
	uint64_t Message::MessageCounter = 0;

	Message::Message(MessageSource messageSource, MessageType messageType, bool reliable)
	{
		Clear();
		SetMessageSource(messageSource);
		SetMessageType(messageType);
		
		m_Reliable = reliable;

		MessageCounter++;
		m_ID = MessageCounter;
	}

	void Message::SetMessageSource(const MessageSource& messageSource)
	{
		MessageSource* messageSourcePtr = reinterpret_cast<MessageSource*>(&m_Buffer[0]);
		*messageSourcePtr = static_cast<MessageSource>(UE_UINT16_NTOH(messageSource));
	}

	MessageSource Message::GetMessageSource()
	{
		MessageSource* messageSourcePtr = reinterpret_cast<MessageSource*>(&m_Buffer[0]);
		return static_cast<MessageSource>(UE_UINT16_HTON(*messageSourcePtr));
	}

	void Message::SetMessageType(const MessageType& messageType)
	{
		MessageType* messageTypePtr = reinterpret_cast<MessageType*>(&m_Buffer[2]);
		*messageTypePtr = static_cast<MessageType>(UE_UINT16_NTOH(*messageTypePtr));
	}

	MessageType Message::GetMessageType()
	{
		MessageType* messageTypePtr = reinterpret_cast<MessageType*>(&m_Buffer[2]);
		return static_cast<MessageType>(UE_UINT16_HTON(*messageTypePtr));
	}

	void Message::Clear()
	{
		uint16_t HeaderSize = sizeof(MessageSource) + sizeof(MessageType);
		m_Buffer.resize(HeaderSize);
		SetMessageSource(0);
		SetMessageType(MessageType::Invalid);
		m_ExtractionOffset = HeaderSize;
	}

	void Message::Append(const void* data, uint32_t size)
	{
		if ((m_Buffer.size() + size) > UE_MAX_MESSAGE_SIZE)
		{
			UE_CORE_ERROR("Message size exceeds max message size!");
			return;
		}

		m_Buffer.insert(m_Buffer.end(), (char*)data, (char*)data + size);
	}

	Message& Message::operator<<(bool data)
	{
		Append(&data, sizeof(bool));
		return *this;
	}

	Message& Message::operator>>(bool& data)
	{
		if (m_ExtractionOffset + sizeof(bool) > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size");
		}

		data = *reinterpret_cast<bool*>(&m_Buffer[m_ExtractionOffset]);
		m_ExtractionOffset += sizeof(bool);
		return *this;
	}
	
	Message& Message::operator<<(uint16_t data)
	{
		data = UE_UINT16_HTON(data);
		Append(&data, sizeof(uint16_t));
		return *this;
	}

	Message& Message::operator>>(uint16_t& data)
	{
		if (m_ExtractionOffset + sizeof(uint16_t) > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size");
		}

		data = *reinterpret_cast<uint16_t*>(&m_Buffer[m_ExtractionOffset]);
		data = UE_UINT16_NTOH(data);
		m_ExtractionOffset += sizeof(uint16_t);
		return *this;
	}

	Message& Message::operator<<(uint32_t data)
	{
		data = UE_UINT32_HTON(data);
		Append(&data, sizeof(uint32_t));
		return *this;
	}

	Message& Message::operator>>(uint32_t& data)
	{
		if (m_ExtractionOffset + sizeof(uint32_t) > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size");
		}

		data = *reinterpret_cast<uint32_t*>(&m_Buffer[m_ExtractionOffset]);
		data = UE_UINT32_NTOH(data);
		m_ExtractionOffset += sizeof(uint32_t);
		return *this;
	}

	Message& Message::operator<<(uint64_t data)
	{
		data = UE_UINT64_HTON(data);
		Append(&data, sizeof(uint64_t));
		return *this;
	}

	Message& Message::operator>>(uint64_t& data)
	{
		if (m_ExtractionOffset + sizeof(uint64_t) > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size");
		}

		data = *reinterpret_cast<uint64_t*>(&m_Buffer[m_ExtractionOffset]);
		data = UE_UINT64_NTOH(data);
		m_ExtractionOffset += sizeof(uint64_t);
		return *this;
	}

	Message& Message::operator<<(int16_t data)
	{
		data = UE_INT16_HTON(data);
		Append(&data, sizeof(int16_t));
		return *this;
	}

	Message& Message::operator>>(int16_t& data)
	{
		if (m_ExtractionOffset + sizeof(int16_t) > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size");
		}

		data = *reinterpret_cast<int16_t*>(&m_Buffer[m_ExtractionOffset]);
		data = UE_INT16_NTOH(data);
		m_ExtractionOffset += sizeof(int16_t);
		return *this;
	}

	Message& Message::operator<<(int32_t data)
	{
		data = UE_INT32_HTON(data);
		Append(&data, sizeof(int32_t));
		return *this;
	}

	Message& Message::operator>>(int32_t& data)
	{
		if (m_ExtractionOffset + sizeof(int32_t) > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size");
		}

		data = *reinterpret_cast<int32_t*>(&m_Buffer[m_ExtractionOffset]);
		data = UE_INT32_NTOH(data);
		m_ExtractionOffset += sizeof(int32_t);
		return *this;
	}

	Message& Message::operator<<(int64_t data)
	{
		data = UE_INT64_HTON(data);
		Append(&data, sizeof(int64_t));
		return *this;
	}

	Message& Message::operator>>(int64_t& data)
	{
		if (m_ExtractionOffset + sizeof(int64_t) > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size");
		}

		data = *reinterpret_cast<int64_t*>(&m_Buffer[m_ExtractionOffset]);
		data = UE_INT64_NTOH(data);
		m_ExtractionOffset += sizeof(int64_t);
		return *this;
	}

	Message& Message::operator<<(float data)
	{
		data = UE_FLOAT_HTON(data);
		Append(&data, sizeof(float));
		return *this;
	}

	Message& Message::operator>>(float& data)
	{
		if (m_ExtractionOffset + sizeof(float) > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size");
		}

		data = *reinterpret_cast<float*>(&m_Buffer[m_ExtractionOffset]);
		data = UE_FLOAT_NTOH(data);
		m_ExtractionOffset += sizeof(float);
		return *this;
	}

	Message& Message::operator<<(double data)
	{
		data = UE_DOUBLE_HTON(data);
		Append(&data, sizeof(double));
		return *this;
	}

	Message& Message::operator>>(double& data)
	{
		if (m_ExtractionOffset + sizeof(double) > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size");
		}

		data = *reinterpret_cast<double*>(&m_Buffer[m_ExtractionOffset]);
		data = UE_DOUBLE_NTOH(data);
		m_ExtractionOffset += sizeof(double);
		return *this;
	}

	Message& Message::operator<<(std::string data)
	{
		*this << (uint32_t)data.size();
		Append(data.data(), data.size());
		return *this;
	}

	Message& Message::operator>>(std::string& data)
	{
		data.clear();

		uint32_t StringSize = 0;
		*this >> StringSize;

		if ((m_ExtractionOffset + StringSize) > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size");
		}

		data.resize(StringSize);
		data.assign(&m_Buffer[m_ExtractionOffset], StringSize);
		m_ExtractionOffset += StringSize;
		return *this;
	}
}