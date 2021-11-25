#include "uepch.h"
#include "Script/Lune/LuneEnum.h"

namespace UE
{
	void LuneEnum::Register(lua_State* L, UEUint32 index)
	{
		lua_pushinteger(L, Value);
		lua_setfield(L, index, Name.c_str());
	}

	void LuneEnum::RegisterSelf(Ref<LuneStack> stack)
	{
		lua_pushinteger(stack->L, Value);
		lua_setglobal(stack->L, Name.c_str());
	}
}