#pragma once

#include "Core/Base.hpp"

namespace UE
{
	class GlobalConfigurationSerializer
	{
	public:
		static UEResult<> Serialize();
		static UEResult<> Deserialize();
	};
}
