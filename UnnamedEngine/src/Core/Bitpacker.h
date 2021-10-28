#pragma once

#include "Core/Bitwise.h"

// Todo: empty the container after end of unpacking

namespace UE
{
	class Bitpacker
	{
	public:
		Bitpacker();
		~Bitpacker();

		template<typename T>
		Bitpacker& PackBits(T data, T maxValue)
		{
			WriteBitStream(data, CalculateRequiredBits(maxValue), m_Packer, m_PackerPosition, m_RawData);

			return *this;
		}

		template<typename T>
		Bitpacker& PackBits(bool data, T maxValue)
		{
			WriteBitStream(data, 1, m_Packer, m_PackerPosition, m_RawData);

			return *this;
		}

		template<typename TD, typename TV>
		Bitpacker& UnpackBits(TD& data, TV maxValue)
		{
			ReadBitStream(data, m_UnpackerPosition, CalculateRequiredBits(maxValue), m_RawData);

			return *this;
		}

		template<typename TV>
		Bitpacker& UnpackBits(bool& data, TV maxValue)
		{
			ReadBitStream(data, m_UnpackerPosition, 1, m_RawData);

			return *this;
		}

		UEUint64 GetPackedBitSize() { return m_RawData.size() * 64; }
		std::deque<UEUint64> m_RawData;

		void EndPacking();

	private:
		UEUint64 m_Packer = 0;
		UEUint8 m_PackerPosition = 1;
		UEUint8 m_UnpackerPosition = 1;
	};
}