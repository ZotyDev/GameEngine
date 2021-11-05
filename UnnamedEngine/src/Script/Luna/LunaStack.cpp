#include "uepch.h"
#include "Script/Luna/LunaStack.h"

#include "Script/LuaAPI.h"

namespace UE
{
	LunaStack::LunaStack()
	{
		L = (luaL_newstate());
		luaL_openlibs(L);
	}

	UEResult LunaStack::ExecuteLine(const UEString& line)
	{
		if (UE_LUAF(luaL_dostring, line.c_str()) == UEResult::Error)
		{
			UE_LUA_ERROR("Failed to execute string");
			return UEResult::Error;
		}

		return UEResult::Success;
	}

	UEResult LunaStack::ExecuteFile(const UEString& path)
	{
		if (UE_LUAF(luaL_dofile, path.c_str()) == UEResult::Error)
		{
			UE_LUA_ERROR("Failed to execute file");
			return UEResult::Error;
		}

		return UEResult::Success;
	}

	UEResult LunaStack::PushGlobalFunction(const UEString& name, lua_CFunction function)
	{
		lua_pushcfunction(L, function);
		lua_setglobal(L, name.c_str());

		return UEResult::Success;
	}

	void LunaStack::LunaStack::Dump()
	{
		UEUint32 Index = lua_gettop(L);
		UE_LUA_TRACE("Dumping Lua stack: total size is {0}", Index);
		while (Index)
		{
			UEUint32 Type = lua_type(L, Index);
			switch (Type)
			{
			case LUA_TSTRING:
				UE_LUA_TRACE("\"{0}\"", lua_tostring(L, Index));
				break;
			case LUA_TBOOLEAN:
				UE_LUA_TRACE("{0}", lua_toboolean(L, Index) ? true : false);
				break;
			case LUA_TNUMBER:
				UE_LUA_TRACE("{0}", lua_tonumber(L, Index));
				break;
			default:
				UE_LUA_TRACE("{0}", lua_typename(L, Type));
				break;
			}
			Index--;
		}
	}
}