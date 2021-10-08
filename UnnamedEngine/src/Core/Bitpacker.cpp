#include "uepch.h"
#include "Bitpacker.h"

namespace UE
{
	Bitpacker::Bitpacker()
	{}

	Bitpacker::~Bitpacker()
	{}

	Bitpacker& Bitpacker::operator<<(UEBool data)
	{
		WriteBitStream(data, 1, m_Packer, m_Index, m_RawData);

		return *this;
	}

	Bitpacker& Bitpacker::operator>>(UEBool& data)
	{
		return *this;
	}
}