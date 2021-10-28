#include "uepch.h"
#include "Bitpacker.h"

namespace UE
{
	Bitpacker::Bitpacker()
	{}

	Bitpacker::~Bitpacker()
	{}

	void Bitpacker::EndPacking()
	{
		m_RawData.push_back(m_Packer);
		m_Packer = 0;
		m_PackerPosition = 1;
	}
}