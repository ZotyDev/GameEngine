#include "uepch.h"
#include "Network/Message.h"

namespace UE
{
	MessageLayout::MessageLayout(int size)
	{
		Elements.resize(size);
	}

	UEResult MessageLayoutLibrary::RegisterMessageLayout(std::string name, const Ref<MessageLayout>& messageLayout)
	{
		auto it = m_MessageLayouts.find(name);
		if (it != m_MessageLayouts.end())
		{
			UE_CORE_ERROR("Failed to register message layout: already registered");
			return UEResult::Error;
		}

		m_MessageLayouts.insert({ name, messageLayout });

		return UEResult::Success;
	}

	uint64_t Message::MessageCounter = 0;

	Message::Message(bool reliable)
	{
		Clear();
		m_Reliable = reliable;
		m_ID = MessageCounter++;
	}

	void Message::Clear()
	{
		m_ExtractionOffset = 0;
	}

	void Message::Append(const void* data, uint32_t size)
	{
		if ((m_Buffer.size() + size) > UE_MAX_MESSAGE_SIZE)
		{
			UE_CORE_ERROR("Message size exceeds max message size");
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
			UE_CORE_ERROR("Extraction offset exceeded buffer size: bool\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), m_ExtractionOffset + sizeof(uint16_t));
		}

		data = *reinterpret_cast<bool*>(&m_Buffer[m_ExtractionOffset]);
		m_ExtractionOffset += sizeof(bool);
		return *this;
	}
	
	Message& Message::operator<<(char data)
	{
		Append(&data, sizeof(char));
		return *this;
	}

	Message& Message::operator>>(char& data)
	{
		if (m_ExtractionOffset + sizeof(char) > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size: char\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), m_ExtractionOffset + sizeof(uint16_t));
		}

		data = *reinterpret_cast<char*>(&m_Buffer[m_ExtractionOffset]);
		m_ExtractionOffset += sizeof(char);
		return *this;
	}

	Message& Message::operator<<(uint8_t data)
	{
		Append(&data, sizeof(uint8_t));
		return *this;
	}

	Message& Message::operator>>(uint8_t& data)
	{
		if (m_ExtractionOffset + sizeof(uint8_t) > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size: uint8_t\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), m_ExtractionOffset + sizeof(uint16_t));
		}

		data = *reinterpret_cast<uint8_t*>(&m_Buffer[m_ExtractionOffset]);
		m_ExtractionOffset += sizeof(uint8_t);
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
			UE_CORE_ERROR("Extraction offset exceeded buffer size: uint16_t\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), m_ExtractionOffset + sizeof(uint16_t));
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
			UE_CORE_ERROR("Extraction offset exceeded buffer size: uint32_t\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), m_ExtractionOffset + sizeof(uint16_t));
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
			UE_CORE_ERROR("Extraction offset exceeded buffer size: uint64_t\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), m_ExtractionOffset + sizeof(uint16_t));
		}

		data = *reinterpret_cast<uint64_t*>(&m_Buffer[m_ExtractionOffset]);
		data = UE_UINT64_NTOH(data);
		m_ExtractionOffset += sizeof(uint64_t);
		return *this;
	}

	Message& Message::operator<<(int8_t data)
	{
		Append(&data, sizeof(int8_t));
		return *this;
	}

	Message& Message::operator>>(int8_t& data)
	{
		if (m_ExtractionOffset + sizeof(int8_t) > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size: int8_t\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), m_ExtractionOffset + sizeof(uint16_t));
		}

		data = *reinterpret_cast<int8_t*>(&m_Buffer[m_ExtractionOffset]);
		m_ExtractionOffset += sizeof(int8_t);
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
			UE_CORE_ERROR("Extraction offset exceeded buffer size: int16_t\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), m_ExtractionOffset + sizeof(uint16_t));
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
			UE_CORE_ERROR("Extraction offset exceeded buffer size: int32_t\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), m_ExtractionOffset + sizeof(uint16_t));
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
		UE_CORE_TRACE(m_ExtractionOffset);
		if (m_ExtractionOffset + sizeof(int64_t) > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size: int64_t\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), m_ExtractionOffset + sizeof(uint16_t));
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
			UE_CORE_ERROR("Extraction offset exceeded buffer size: float\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), m_ExtractionOffset + sizeof(uint16_t));
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
			UE_CORE_ERROR("Extraction offset exceeded buffer size: double\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), m_ExtractionOffset + sizeof(uint16_t));
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
			UE_CORE_ERROR("Extraction offset exceeded buffer size: string\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), m_ExtractionOffset + sizeof(uint16_t));
		}

		data.resize(StringSize);
		data.assign(&m_Buffer[m_ExtractionOffset], StringSize);
		m_ExtractionOffset += StringSize;
		return *this;
	}
}