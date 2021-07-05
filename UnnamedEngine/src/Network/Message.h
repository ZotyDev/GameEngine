#pragma once

#define UE_MAX_MESSAGE_SIZE 128

namespace UE
{
	class Message
	{
	public:
		Message(bool reliable = true);

		void Reliable(bool reliable = true) { m_Reliable = reliable; }
		bool IsReliable() { return m_Reliable; }

		void Clear();
		void Append(const void* data, uint32_t size);

		uint32_t GetMessageSize() { return m_Buffer.size(); }

		std::vector<char> GetBuffer() { return m_Buffer; }
		void SetBuffer(std::vector<char> buffer) { m_Buffer = buffer; }

		Message& operator << (bool data);
		Message& operator >> (bool& data);

		Message& operator << (char data);
		Message& operator >> (char& data);

		Message& operator << (uint8_t data);
		Message& operator >> (uint8_t& data);

		Message& operator << (uint16_t data);
		Message& operator >> (uint16_t& data);

		Message& operator << (uint32_t data);
		Message& operator >> (uint32_t& data);

		Message& operator << (uint64_t data);
		Message& operator >> (uint64_t& data);

		Message& operator << (int8_t data);
		Message& operator >> (int8_t& data);

		Message& operator << (int16_t data);
		Message& operator >> (int16_t& data);

		Message& operator << (int32_t data);
		Message& operator >> (int32_t& data);

		Message& operator << (int64_t data);
		Message& operator >> (int64_t& data);

		Message& operator << (float data);
		Message& operator >> (float& data);

		Message& operator << (double data);
		Message& operator >> (double& data);

		Message& operator << (std::string data);
		Message& operator >> (std::string& data);

		std::vector<char> m_Buffer;
		uint32_t m_ExtractionOffset = 0;
		bool m_Reliable = false;
		uint64_t m_ID = 0;
	private:
		static uint64_t MessageCounter;
	};

	enum class MessageDataType
	{
		None = 0,
		Bool,
		Char,
		Uint8, Uint16, Uint32, Uint64,
		Int8, Int16, Int32, Int64,
		Float, Double,

		Int = Int32
	};

	static uint32_t MessageDataTypeSize(MessageDataType type)
	{
		switch (type)
		{
			case MessageDataType::Bool:		return 1;
			case MessageDataType::Char:		return 1;
			case MessageDataType::Uint8:	return 1;
			case MessageDataType::Uint16:	return 2;
			case MessageDataType::Uint32:	return 4;
			case MessageDataType::Uint64:	return 8;
			case MessageDataType::Int8:		return 1;
			case MessageDataType::Int16:	return 2;
			case MessageDataType::Int32:	return 4;
			case MessageDataType::Int64:	return 8;
			case MessageDataType::Float:	return 4;
			case MessageDataType::Double:	return 8;
		}

		UE_CORE_ERROR("Unknown MessageDataType");
		return 0;
	}

	struct MessageElement
	{
		std::string Name;
		MessageDataType Type;
		std::vector<UnknownType> Data;
		uint32_t ElementSize;
		uint32_t ElementCount;

		MessageElement(MessageDataType type, const std::string& name, uint32_t elementCount = 1)
			: Name(name), Type(type), ElementSize(0), ElementCount(elementCount)
		{
			Data.resize(elementCount, nullptr);
		}
	};

	class MessageLayout
	{
	public:
		MessageLayout() {}

		MessageLayout(const std::vector<MessageElement>& elements)
			: m_Elements(elements)
		{
			CalculateSize();
		}

		uint32_t GetSize() { return m_Elements.size(); }

		int SetElements(const std::vector<UE::UnknownType>& elements)
		{
			uint32_t NumberOfGivenElements = elements.size();
			uint32_t NumberOfRequiredElements = m_Elements.size();
			if (NumberOfGivenElements != NumberOfRequiredElements)
			{
				UE_CORE_ERROR("Failed to set elements of message: invalid number of elements given, expected {0} got {1}", NumberOfRequiredElements, NumberOfGivenElements);
				return -1;
			}

			for (int i = 0; i < NumberOfGivenElements; i++)
			{
				m_Elements[i].Data[0] = elements[i];
			}

			return 0;
		}

		std::vector<UE::UnknownType> GetElements()
		{
			std::vector<UE::UnknownType> UnknownData;
			UnknownData.resize(m_Elements.size());
			for (int i = 0; i < UnknownData.size(); i++)
			{
				UnknownData[i] = m_Elements[i].Data[0];
			}

			return UnknownData;
		}

		int CreateMessage(Message& message)
		{
			for (auto& element : m_Elements)
			{
				switch (element.Type)
				{
				case MessageDataType::Bool:
					message << UE::FromUknown<bool>(element.Data[0]);
					break;
				case MessageDataType::Char:
					message << UE::FromUknown<char>(element.Data[0]);
					break;
				case MessageDataType::Uint8:
					message << UE::FromUknown<uint8_t>(element.Data[0]);
					break;
				case MessageDataType::Uint16:
					message << UE::FromUknown<uint16_t>(element.Data[0]);
					break;
				case MessageDataType::Uint32:
					message << UE::FromUknown<uint32_t>(element.Data[0]);
					break;
				case MessageDataType::Uint64:
					message << UE::FromUknown<uint64_t>(element.Data[0]);
					break;
				case MessageDataType::Int8:
					message << UE::FromUknown<int8_t>(element.Data[0]);
					break;
				case MessageDataType::Int16:
					message << UE::FromUknown<int16_t>(element.Data[0]);
					break;
				case MessageDataType::Int32:
					message << UE::FromUknown<int32_t>(element.Data[0]);
					break;
				case MessageDataType::Int64:
					message << UE::FromUknown<int64_t>(element.Data[0]);
					break;
				case MessageDataType::Float:
					message << UE::FromUknown<float>(element.Data[0]);
					break;
				case MessageDataType::Double:
					message << UE::FromUknown<double>(element.Data[0]);
					break;
				}
			}

			return 0;
		}

		int FromMessage(Message& message)
		{
			for (auto& element : m_Elements)
			{
				switch (element.Type)
				{
				case MessageDataType::Bool:
				{
					bool ReceivedData;
					message >> ReceivedData;
					element.Data[0] = UE::CreateUnknown(&ReceivedData);
					break;
				}
				case MessageDataType::Char:
				{
					char ReceivedData;
					message >> ReceivedData;
					element.Data[0] = UE::CreateUnknown(&ReceivedData);
					break;
				}
				case MessageDataType::Uint8:
				{
					uint8_t ReceivedData;
					message >> ReceivedData;
					element.Data[0] = UE::CreateUnknown(&ReceivedData);
					break;
				}
				case MessageDataType::Uint16:
				{
					uint16_t ReceivedData;
					message >> ReceivedData;
					element.Data[0] = UE::CreateUnknown(&ReceivedData);
					break;
				}
				case MessageDataType::Uint32:
				{
					uint32_t ReceivedData;
					message >> ReceivedData;
					element.Data[0] = UE::CreateUnknown(&ReceivedData);
					break;
				}
				case MessageDataType::Uint64:
				{
					uint64_t ReceivedData;
					message >> ReceivedData;
					element.Data[0] = UE::CreateUnknown(&ReceivedData);
					break;
				}
				case MessageDataType::Int8:
				{
					int8_t ReceivedData;
					message >> ReceivedData;
					element.Data[0] = UE::CreateUnknown(&ReceivedData);
					break;
				}
				case MessageDataType::Int16:
				{
					int16_t ReceivedData;
					message >> ReceivedData;
					element.Data[0] = UE::CreateUnknown(&ReceivedData);
					break;
				}
				case MessageDataType::Int32:
				{
					int32_t ReceivedData;
					message >> ReceivedData;
					element.Data[0] = UE::CreateUnknown(&ReceivedData);
					break;
				}
				case MessageDataType::Int64:
				{
					int64_t ReceivedData;
					message >> ReceivedData;
					element.Data[0] = UE::CreateUnknown(&ReceivedData);
					break;
				}
				case MessageDataType::Float:
				{
					float ReceivedData;
					message >> ReceivedData;
					element.Data[0] = UE::CreateUnknown(&ReceivedData);
					break;
				}
				case MessageDataType::Double:
				{
					double ReceivedData;
					message >> ReceivedData;
					element.Data[0] = UE::CreateUnknown(&ReceivedData);
					break;
				}
				}
			}

			return 0;
		}

		std::vector<MessageElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<MessageElement>::iterator end() { return m_Elements.end(); }
		std::vector<MessageElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<MessageElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateSize()
		{
			for (auto& element : m_Elements)
			{
				element.ElementSize = MessageDataTypeSize(element.Type);
			}
		}
	private:
		std::vector<MessageElement> m_Elements;
	};

	class MessageLayoutLibrary
	{
	public:

	private:
	};
}