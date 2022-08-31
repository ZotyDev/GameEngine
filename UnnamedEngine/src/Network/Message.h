#pragma once

#define UE_MAX_MESSAGE_SIZE 128

namespace UE
{
	class Message
	{
	public:
		Message(UEBool realible);

		UEResult<> Clear();
		UEResult<> Append(const void* data, UEUint32 size);

		UEUint32 GetMessageSize() { return m_Buffer.size(); }

		UEResult<> InsertData(UEBool data);
		UEResult<> InsertData(UEChar data);
		UEResult<> InsertData(UEInt8 data);
		UEResult<> InsertData(UEInt16 data);
		UEResult<> InsertData(UEInt32 data);
		UEResult<> InsertData(UEInt64 data);
		UEResult<> InsertData(UEUint8 data);
		UEResult<> InsertData(UEUint16 data);
		UEResult<> InsertData(UEUint32 data);
		UEResult<> InsertData(UEUint64 data);
		UEResult<> InsertData(UEFloat data);
		UEResult<> InsertData(UEDouble data);
		UEResult<> InsertData(const UEString& data);

		UEResult<> GetData(UEBool& data);
		UEResult<> GetData(UEChar& data);
		UEResult<> GetData(UEInt8& data);
		UEResult<> GetData(UEInt16& data);
		UEResult<> GetData(UEInt32& data);
		UEResult<> GetData(UEInt64& data);
		UEResult<> GetData(UEUint8& data);
		UEResult<> GetData(UEUint16& data);
		UEResult<> GetData(UEUint32& data);
		UEResult<> GetData(UEUint64& data);
		UEResult<> GetData(UEFloat& data);
		UEResult<> GetData(UEDouble& data);
		UEResult<> GetData(UEString& data);

	public:
		UEBool m_Reliable;
		std::vector<char> m_Buffer;
		UEUint32 m_ExtractionOffset = 0;
	};
}