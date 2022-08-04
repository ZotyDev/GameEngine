#include "uepch.h"
#include "Core/Base.h"

namespace UE
{
	UEInt8 UEResult::Error = -1;
	UEInt8 UEResult::Success = 0;
	UEInt8 UEResult::Warn = 1;
	UEInt8 UEResult::Undefined = UE_INT8_MAX;

	UEResult::UEResult()
		: m_Result(UEResult::Undefined) {}

	UEResult::UEResult(UEInt8 result)
		: m_Result(result) {}

	UEResult::operator UEBool() const
	{
		return (m_Result == UEResult::Success);
	}

	UEResult& UEResult::operator = (UEInt8 result)
	{
		m_Result = result;
		return *this;
	}
}