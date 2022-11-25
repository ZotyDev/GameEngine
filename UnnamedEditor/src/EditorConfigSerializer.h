#pragma once

namespace UE
{
	class EditorConfigSerializer
	{
	public:
		static UEResult<> Serialize();
		static UEResult<> Deserialize();
	};
}