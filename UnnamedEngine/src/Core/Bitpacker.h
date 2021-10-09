#pragma once

#include "Core/Bitwise.h"

namespace UE
{
	class Bitpacker
	{
	public:
		Bitpacker();
		~Bitpacker();

		template<typename T>
		Bitpacker& operator << (T data)
		{
			WriteBitStream(data, CalculateRequiredBits(data), m_Packer, m_Index, m_RawData);

			return *this;
		}

		template<typename T>
		Bitpacker& operator >> (T& data)
		{
			return *this;
		}

		Bitpacker& operator << (UEBool data);
		Bitpacker& operator >> (UEBool& data);

		void EndPacking();

	private:
		UEUint64 m_Packer = 0;
		UEUint8 m_Index = 0;
		UEUint64 m_Counter = 0;

		std::vector<UEUint64> m_RawData;
	};
}