#include "uepch.h"
#include "Script/Lune/LuneFunction.h"

namespace UE
{
	void LuneFunction::Register(LuneStack stack)
	{
		lua_pushcfunction(stack.L, Function);
		lua_setglobal(stack.L, Name.c_str());
	}

	void LuneFunction::Register(LuneStack stack, void* userPtr)
	{
		lua_pushlightuserdata(stack.L, userPtr);
		lua_pushcclosure(stack.L, Function, 1);
		lua_setglobal(stack.L, Name.c_str());
	}

	void LuneFunction::RegisterSelf(lua_State* L, UEUint32 index)
	{
		lua_pushcfunction(L, Function);
		lua_setfield(L, index, Name.c_str());
	}
}