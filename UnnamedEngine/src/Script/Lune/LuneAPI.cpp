#include "uepch.h"
#include "Script/Lune/LuneAPI.h"

namespace UE
{
	UEResult<> LuneErrorCheck(lua_State* L, int status)
	{
		if (status != LUA_OK)
		{
			if (lua_isstring(L, -1))
			{
				UE_LUA_ERROR(lua_tostring(L, -1));
				lua_pop(L, 1);

				return UEResult<>::Error;
			}
			UE_LUA_ERROR("Unknown error");
			return UEResult<>::Error;
		}
		return UEResult<>::Success;
	}

	void LuneStack::Dump()
	{
		UEUint32 Index = lua_gettop(L);
		UE_LUA_TRACE("Dumping Lua stack: total size is {0}", Index);
		while (Index)
		{
			UEUint32 Type = lua_type(L, Index);
			switch (Type)
			{
			case LUA_TNIL:
				UE_LUA_TRACE("nil");
				break;
			case LUA_TSTRING:
				UE_LUA_TRACE("String: \"{0}\"", lua_tostring(L, Index));
				break;
			case LUA_TBOOLEAN:
				UE_LUA_TRACE("Boolean: {0}", lua_toboolean(L, Index) ? true : false);
				break;
			case LUA_TNUMBER:
				UE_LUA_TRACE("Number: {0}", lua_tonumber(L, Index));
				break;
			case LUA_TFUNCTION:
				UE_LUA_TRACE("Function");
				break;
			case LUA_TTABLE:
				UE_LUA_TRACE("Table");
				break;
			default:
				UE_LUA_TRACE("{0}", lua_typename(L, Type));
				break;
			}
			Index--;
		}
	};

	UEResult<> LuneStack::ExecuteLine(const UEString& line)
	{
		if (!UE_LUAF(luaL_dostring, line.c_str()))
		{
			UE_LUA_ERROR("Failed to execute string");
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	};

	UEResult<> LuneStack::ExecuteFile(const UEString& path)
	{
		if (!UE_LUAF(luaL_dofile, path.c_str()))
		{
			UE_LUA_ERROR("Failed to execute file");
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	};
}