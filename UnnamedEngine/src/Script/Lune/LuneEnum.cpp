#include "uepch.h"
#include "Script/Lune/LuneEnum.h"

namespace UE
{
	LuneEnum::LuneEnum(const UEString& name, UEUint16 value)
		: Name(name), Value(value)
	{}

	LuneEnum::LuneEnum(const UEString& name, UEUint32 value)
		: Name(name), Value(value)
	{}

	LuneEnum::LuneEnum(const UEString& name, UEUint64 value)
		: Name(name), Value(value)
	{}

	void LuneEnum::RegisterSelf(lua_State* L, UEUint32 index)
	{
		lua_pushinteger(L, Value);
		lua_setfield(L, index, Name.c_str());
	}
}