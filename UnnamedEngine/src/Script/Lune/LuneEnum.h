#pragma once

#include "Script/Lune/LuneAPI.h"

namespace UE
{
	class LuneEnum
	{
	public:
		LuneEnum(const UEString& name, UEUint16 value);
		LuneEnum(const UEString& name, UEUint32 value);
		LuneEnum(const UEString& name, UEUint64 value);

		void RegisterSelf(lua_State* L, UEUint32 index);

		UEString Name;
		UEUint64 Value;
	};
}