#pragma once

#define UE_MAX_MESSAGE_SIZE 128

namespace UE
{
	typedef uint16_t MessageSource;

	enum MessageType : uint16_t
	{
		Continuation,
		Invalid
	};

	class Message
	{
	public:
		Message(MessageSource messageSource, MessageType messageType, bool reliable = true);

		void SetMessageSource(const MessageSource& messageSource);
		MessageSource GetMessageSource();
		void SetMessageType(const MessageType& messageType);
		MessageType GetMessageType();

		void Reliable(bool reliable = true) { m_Reliable = reliable; }
		bool IsReliable() { return m_Reliable; }

		void Clear();
		void Append(const void* data, uint32_t size);

		uint32_t GetMessageSize() { return m_Buffer.size(); }

		std::vector<char> GetBuffer() { return m_Buffer; }
		void SetBuffer(std::vector<char> buffer) { m_Buffer = buffer; }

		Message& operator << (bool data);
		Message& operator >> (bool& data);

		Message& operator << (uint16_t data);
		Message& operator >> (uint16_t& data);

		Message& operator << (uint32_t data);
		Message& operator >> (uint32_t& data);

		Message& operator << (uint64_t data);
		Message& operator >> (uint64_t& data);

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

	private:
		std::vector<char> m_Buffer;
		uint32_t m_ExtractionOffset = 0;
		bool m_Reliable = false;
		uint64_t m_ID = 0;
	private:
		static uint64_t MessageCounter;
	};
}