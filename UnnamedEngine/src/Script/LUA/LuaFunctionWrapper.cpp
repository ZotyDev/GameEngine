#include "uepch.h"
#include "Script/LUA/LuaFunctionWrapper.h"

namespace UE
{
	UEResult LuaErrorCheckFunction(lua_State* L, int status)
	{
		if (status != LUA_OK)
		{
			if (lua_isstring(L, -1))
			{
				UE_LUA_ERROR(lua_tostring(L, -1));
				lua_pop(L, 1);

				return UEResult::Error;
			}

			UE_LUA_ERROR("Unknown error");

			return UEResult::Error;
		}
		return UEResult::Success;
	}

	UEResult LuaRegisterFunction(lua_State* L, const std::string& fnName, lua_CFunction fn)
	{
		lua_pushcclosure(L, fn, 0);
		lua_setglobal(L, fnName.c_str());

		return UEResult::Success;
	}

	UEResult LuaRegisterFunction(lua_State* L, const std::string& fnName, lua_CFunction fn, void* userPtr)
	{
		lua_pushlightuserdata(L, userPtr);
		lua_pushcclosure(L, fn, 1);
		lua_setglobal(L, fnName.c_str());

		return UEResult::Success;
	}

	UEResult LuaGetBoolean(lua_State* L, int index, bool& value)
	{
		if (!lua_isboolean(L, index))
		{
			UE_LUA_ERROR("Failed to pass value: expected boolean - got {0}", lua_typename(L, lua_type(L, index)));
			return UEResult::Error;
		}

		value = lua_toboolean(L, index);

		return UEResult::Success;
	}

	UEResult LuaGetNumber(lua_State* L, int index, double& value)
	{
		if (!lua_isnumber(L, index))
		{
			UE_LUA_ERROR("Failed to pass value: expected number - got {0}", lua_typename(L, lua_type(L, index)));
			return UEResult::Error;
		}

		value = lua_tonumber(L, index);

		return UEResult::Success;
	}

	UEResult LuaGetString(lua_State* L, int index, char*& value)
	{
		if (!lua_isstring(L, index))
		{
			UE_LUA_ERROR("Failed to pass value: expected string - got {0}", lua_typename(L, lua_type(L, index)));
			return UEResult::Error;
		}

		value = (char*)lua_tostring(L, index);

		return UEResult::Success;
	}

	UEResult LuaPushMetaTableFunction(lua_State* L, const std::string& fnName, lua_CFunction fn)
	{
		lua_pushstring(L, fnName.c_str());
		lua_pushcfunction(L, fn);
		lua_settable(L, -3);

		return UEResult::Success;
	}

	UEResult LuaPushAddFunction(lua_State* L, lua_CFunction fn)
	{
		lua_pushstring(L, "__add");
		lua_pushcfunction(L, fn);
		lua_settable(L, -3);

		return UEResult::Success;
	}

	UEResult LuaPushSubFunction(lua_State* L, lua_CFunction fn)
	{
		lua_pushstring(L, "__sub");
		lua_pushcfunction(L, fn);
		lua_settable(L, -3);

		return UEResult::Success;
	}

	UEResult LuaPushMultFunction(lua_State* L, lua_CFunction fn)
	{
		lua_pushstring(L, "__mul");
		lua_pushcfunction(L, fn);
		lua_settable(L, -3);

		return UEResult::Success;
	}

	UEResult LuaPushDivFunction(lua_State* L, lua_CFunction fn)
	{
		lua_pushstring(L, "__div");
		lua_pushcfunction(L, fn);
		lua_settable(L, -3);

		return UEResult::Success;
	}

	UEResult LuaPushNegaFunction(lua_State* L, lua_CFunction fn)
	{
		lua_pushstring(L, "__unm");
		lua_pushcfunction(L, fn);
		lua_settable(L, -3);

		return UEResult::Success;
	}

	UEResult LuaPushExpoFunction(lua_State* L, lua_CFunction fn)
	{
		lua_pushstring(L, "__pow");
		lua_pushcfunction(L, fn);
		lua_settable(L, -3);

		return UEResult::Success;
	}

	UEResult LuaPushConcatFunction(lua_State* L, lua_CFunction fn)
	{
		lua_pushstring(L, "__concat");
		lua_pushcfunction(L, fn);
		lua_settable(L, -3);

		return UEResult::Success;
	}

	UEResult LuaExecuteFile(lua_State* L, const std::string& filePath)
	{
		if (LuaErrorCheckFunction(L, luaL_dofile(L, filePath.c_str())) == UEResult::Error)
		{
			UE_LUA_ERROR("Failed to execute {0}", filePath);
			return UEResult::Error;
		}

		return UEResult::Success;
	}

	UEResult LuaExecuteString(lua_State* L, const std::string& string)
	{
		if (LuaErrorCheckFunction(L, luaL_dostring(L, string.c_str())) == UEResult::Error)
		{
			UE_LUA_ERROR("Failed to execute string");
			return UEResult::Error;
		}

		return UEResult::Success;
	}
}