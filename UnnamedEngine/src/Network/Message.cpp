#include "uepch.h"
#include "Network/Message.h"

namespace UE
{
	Message::Message(UEBool reliable)
		: m_Reliable(reliable)
	{}

	UEResult Message::Clear()
	{
		m_ExtractionOffset = 0;

		return UEResult::Success;
	}

	UEResult Message::Append(const void* data, UEUint32 size)
	{
		UEUint32 NewSize = m_Buffer.size() + size;
		if (NewSize > UE_MAX_MESSAGE_SIZE)
		{
			UE_CORE_ERROR("Failed to append data to message, max size exceeded: max size is {0}, size after append is {1}", UE_MAX_MESSAGE_SIZE, NewSize);
			return UEResult::Error;
		}
		else
		{
			m_Buffer.insert(m_Buffer.end(), (char*)data, (char*)data + size);
		}

		return UEResult::Success;
	}

	UEResult Message::InsertData(UEBool data)
	{
		return Append(&data, sizeof(UEBool));
	}

	UEResult Message::InsertData(UEChar data)
	{
		return Append(&data, sizeof(UEChar));
	}

	UEResult Message::InsertData(UEInt8 data)
	{
		return Append(&data, sizeof(UEInt8));
	}

	UEResult Message::InsertData(UEInt16 data)
	{
		data = UE_INT16_HTON(data);
		return Append(&data, sizeof(UEInt16));
	}

	UEResult Message::InsertData(UEInt32 data)
	{
		data = UE_INT32_HTON(data);
		return Append(&data, sizeof(UEInt32));
	}

	UEResult Message::InsertData(UEInt64 data)
	{
		data = UE_INT64_HTON(data);
		return Append(&data, sizeof(UEInt64));
	}

	UEResult Message::InsertData(UEUint8 data)
	{
		return Append(&data, sizeof(UEUint8));
	}

	UEResult Message::InsertData(UEUint16 data)
	{
		data = UE_UINT16_HTON(data);
		return Append(&data, sizeof(UEUint16));
	}

	UEResult Message::InsertData(UEUint32 data)
	{
		data = UE_UINT32_HTON(data);
		return Append(&data, sizeof(UEUint32));
	}

	UEResult Message::InsertData(UEUint64 data)
	{
		data = UE_UINT64_HTON(data);
		return Append(&data, sizeof(UEUint64));
	}

	UEResult Message::InsertData(UEFloat data)
	{
		data = UE_FLOAT_HTON(data);
		return Append(&data, sizeof(UEFloat));
	}

	UEResult Message::InsertData(UEDouble data)
	{
		data = UE_DOUBLE_HTON(data);
		return Append(&data, sizeof(UEDouble));
	}

	UEResult Message::InsertData(const UEString& data)
	{
		UEResult Result = UEResult::Success;
		UEUint32 SizeOfMessage = data.size();
		if (SizeOfMessage + m_Buffer.size() > UE_MAX_MESSAGE_SIZE)
		{
			UE_CORE_ERROR("Not enough space for \"{0}\" on current message: max size is {1}, required space is {2}", data, UE_MAX_MESSAGE_SIZE, SizeOfMessage + m_Buffer.size());
			return UEResult::Error;
		}
		Result = InsertData(SizeOfMessage);
		if (InsertData(SizeOfMessage) == UEResult::Error)
		{
			return UEResult::Error;
		}
		for (UEUint32 i = 0; i < SizeOfMessage; i++)
		{
			if (InsertData(data[i]) == UEResult::Error)
			{
				return UEResult::Error;
			}
		}
		return UEResult::Success;
	}

	UEResult Message::GetData(UEBool& data)
	{
		UEUint32 SizeNeeded = m_ExtractionOffset + sizeof(UEBool);
		if (SizeNeeded > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size: bool\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), SizeNeeded);
			return UEResult::Error;
		}
		else
		{
			data = *reinterpret_cast<bool*>(&m_Buffer[m_ExtractionOffset]);
			m_ExtractionOffset += sizeof(UEBool);
			return UEResult::Success;
		}
	}

	UEResult Message::GetData(UEChar& data)
	{
		UEUint32 SizeNeeded = m_ExtractionOffset + sizeof(UEChar);
		if (SizeNeeded > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size: char\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), SizeNeeded);
			return UEResult::Error;
		}
		else
		{
			data = *reinterpret_cast<UEChar*>(&m_Buffer[m_ExtractionOffset]);
			m_ExtractionOffset += sizeof(UEChar);
			return UEResult::Success;
		}
	}

	UEResult Message::GetData(UEInt8& data)
	{
		UEUint32 SizeNeeded = m_ExtractionOffset + sizeof(UEInt8);
		if (SizeNeeded > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size: int8\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), SizeNeeded);
			return UEResult::Error;
		}
		else
		{
			data = *reinterpret_cast<UEInt8*>(&m_Buffer[m_ExtractionOffset]);
			m_ExtractionOffset += sizeof(UEInt8);
			return UEResult::Success;
		}
	}

	UEResult Message::GetData(UEInt16& data)
	{
		UEUint32 SizeNeeded = m_ExtractionOffset + sizeof(UEInt16);
		if (SizeNeeded > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size: int16\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), SizeNeeded);
			return UEResult::Error;
		}
		else
		{
			data = *reinterpret_cast<UEInt16*>(&m_Buffer[m_ExtractionOffset]);
			data = UE_INT16_NTOH(data);
			m_ExtractionOffset += sizeof(UEInt16);
			return UEResult::Success;
		}
	}

	UEResult Message::GetData(UEInt32& data)
	{
		UEUint32 SizeNeeded = m_ExtractionOffset + sizeof(UEInt32);
		if (SizeNeeded > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size: int32\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), SizeNeeded);
			return UEResult::Error;
		}
		else
		{
			data = *reinterpret_cast<UEInt32*>(&m_Buffer[m_ExtractionOffset]);
			data = UE_INT32_NTOH(data);
			m_ExtractionOffset += sizeof(UEInt32);
			return UEResult::Success;
		}
	}

	UEResult Message::GetData(UEInt64& data)
	{
		UEUint32 SizeNeeded = m_ExtractionOffset + sizeof(UEInt64);
		if (SizeNeeded > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size: int64\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), SizeNeeded);
			return UEResult::Error;
		}
		else
		{
			data = *reinterpret_cast<UEInt64*>(&m_Buffer[m_ExtractionOffset]);
			data = UE_INT64_NTOH(data);
			m_ExtractionOffset += sizeof(UEInt64);
			return UEResult::Success;
		}
	}

	UEResult Message::GetData(UEUint8& data)
	{
		UEUint32 SizeNeeded = m_ExtractionOffset + sizeof(UEUint8);
		if (SizeNeeded > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size: uint8\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), SizeNeeded);
			return UEResult::Error;
		}
		else
		{
			data = *reinterpret_cast<UEUint8*>(&m_Buffer[m_ExtractionOffset]);
			m_ExtractionOffset += sizeof(UEUint8);
			return UEResult::Success;
		}
	}

	UEResult Message::GetData(UEUint16& data)
	{
		UEUint32 SizeNeeded = m_ExtractionOffset + sizeof(UEUint16);
		if (SizeNeeded > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size: uint16\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), SizeNeeded);
			return UEResult::Error;
		}
		else
		{
			data = *reinterpret_cast<UEUint16*>(&m_Buffer[m_ExtractionOffset]);
			data = UE_UINT16_NTOH(data);
			m_ExtractionOffset += sizeof(UEUint16);
			return UEResult::Success;
		}
	}

	UEResult Message::GetData(UEUint32& data)
	{
		UEUint32 SizeNeeded = m_ExtractionOffset + sizeof(UEUint32);
		if (SizeNeeded > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size: uint32\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), SizeNeeded);
			return UEResult::Error;
		}
		else
		{
			data = *reinterpret_cast<UEUint32*>(&m_Buffer[m_ExtractionOffset]);
			data = UE_UINT32_NTOH(data);
			m_ExtractionOffset += sizeof(UEUint32);
			return UEResult::Success;
		}
	}

	UEResult Message::GetData(UEUint64& data)
	{
		UEUint32 SizeNeeded = m_ExtractionOffset + sizeof(UEUint64);
		if (SizeNeeded > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size: uint64\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), SizeNeeded);
			return UEResult::Error;
		}
		else
		{
			data = *reinterpret_cast<UEUint64*>(&m_Buffer[m_ExtractionOffset]);
			data = UE_UINT64_NTOH(data);
			m_ExtractionOffset += sizeof(UEUint64);
			return UEResult::Success;
		}
	}

	UEResult Message::GetData(UEFloat& data)
	{
		UEUint32 SizeNeeded = m_ExtractionOffset + sizeof(UEFloat);
		if (SizeNeeded > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size: float\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), SizeNeeded);
			return UEResult::Error;
		}
		else
		{
			data = *reinterpret_cast<UEFloat*>(&m_Buffer[m_ExtractionOffset]);
			data = UE_FLOAT_NTOH(data);
			m_ExtractionOffset += sizeof(UEFloat);
			return UEResult::Success;
		}
	}

	UEResult Message::GetData(UEDouble& data)
	{
		UEUint32 SizeNeeded = m_ExtractionOffset + sizeof(UEDouble);
		if (SizeNeeded > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size: double\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), SizeNeeded);
			return UEResult::Error;
		}
		else
		{
			data = *reinterpret_cast<UEDouble*>(&m_Buffer[m_ExtractionOffset]);
			data = UE_DOUBLE_NTOH(data);
			m_ExtractionOffset += sizeof(UEDouble);
			return UEResult::Success;
		}
	}

	UEResult Message::GetData(UEString& data)
	{
		UEUint32 SizeOfString = 0;
		if (GetData(SizeOfString) == UEResult::Error)
		{
			UE_CORE_ERROR("Failed to get string data size");
			return UEResult::Error;
		}

		m_ExtractionOffset += sizeof(UEUint32);

		if (SizeOfString > m_Buffer.size())
		{
			UE_CORE_ERROR("Extraction offset exceeded buffer size: string\n Buffer size: {0}\n Extraction offset: {1}", m_Buffer.size(), SizeOfString);
			return UEResult::Error;
		}
		else
		{
			data.clear();
			for (UEUint32 i = 0; i < SizeOfString; i++)
			{
				UEChar CurrentChar = 0;
				GetData(CurrentChar);
				data += CurrentChar;
			}
			return UEResult::Success;
		}
	}
}