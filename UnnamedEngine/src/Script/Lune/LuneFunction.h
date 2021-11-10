#pragma once

#include "Script/Lune/LuneAPI.h"

namespace UE
{
	class LuneFunction
	{
	public:
		LuneFunction(const UEString& name, lua_CFunction fn)
			: Name(name), Function(fn)
		{}

		void Register(LuneStack stack);
		void Register(LuneStack stack, void* userPtr);

		void RegisterSelf(lua_State* L, UEUint32 index);

		UEString Name;
		lua_CFunction Function;
		void* UserPtr = nullptr;
	};
}