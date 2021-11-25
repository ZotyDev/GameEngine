#include "uepch.h"
#include "Script/Lune/LuneFunction.h"

namespace UE
{
	void LuneFunction::Register(lua_State* L, UEUint32 index)
	{
		if (UserPtr == nullptr)
		{
			lua_pushcfunction(L, Function);
			lua_setfield(L, index, Name.c_str());
			
			return;
		}
		else
		{
			lua_pushlightuserdata(L, UserPtr);
			lua_pushcclosure(L, Function, 1);
			lua_setfield(L, index, Name.c_str());

			return;
		}
	}

	void LuneFunction::RegisterSelf(Ref<LuneStack> stack)
	{
		lua_State* L = stack->L;

		if (UserPtr == nullptr)
		{
			lua_pushcfunction(L, Function);
			lua_setglobal(L, Name.c_str());

			return;
		}
		else
		{
			lua_pushlightuserdata(L, UserPtr);
			lua_pushcclosure(L, Function, 1);
			lua_setglobal(L, Name.c_str());

			return;
		}
	}
}