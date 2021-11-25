#pragma once

#include "Script/Lune/LuneAPI.h"

namespace UE
{
	class LuneEnum
	{
	public:
		LuneEnum(const UEString& name, UEUint64 value)
			: Name(name), Value(value)
		{}

		void Register(lua_State* L, UEUint32 index);
		void RegisterSelf(Ref<LuneStack> stack);

		UEString Name;
		UEUint64 Value;
	};
}