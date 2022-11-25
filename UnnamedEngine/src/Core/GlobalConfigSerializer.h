#pragma once

namespace UE
{
	class GlobalConfigSerializer
	{
	public:
		static UEResult<> Serialize();
		static UEResult<> Deserialize();
	};
}