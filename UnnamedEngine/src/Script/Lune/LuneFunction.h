#pragma once

#include "Script/Lune/LuneAPI.h"

namespace UE
{
	class LuneFunction
	{
	public:
		LuneFunction(const UEString& name, lua_CFunction fn, void* userPtr = nullptr)
			: Name(name), Function(fn), UserPtr(userPtr)
		{}

		void Register(lua_State* L, UEUint32 index);
		void RegisterSelf(Ref<LuneStack> stack);

		UEString Name;
		lua_CFunction Function;
		void* UserPtr;
	};
}