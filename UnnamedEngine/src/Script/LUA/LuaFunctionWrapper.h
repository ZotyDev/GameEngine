#pragma once

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

namespace UE
{
	UEResult LuaRegisterFunction(lua_State* L, const std::string& fnName, lua_CFunction fn);
	UEResult LuaRegisterFunction(lua_State* L, const std::string& fnName, lua_CFunction fn, void* userPtr);

	UEResult LuaGetBoolean(lua_State* L, int index, bool& value);
	UEResult LuaGetNumber(lua_State* L, int index, double& value);
	UEResult LuaGetString(lua_State* L, int index, char*& value);

	UEResult LuaPushMetaTableFunction(lua_State* L, const std::string& fnName, lua_CFunction fn);

	UEResult LuaPushAddFunction(lua_State* L, lua_CFunction fn);
	UEResult LuaPushSubFunction(lua_State* L, lua_CFunction fn);
	UEResult LuaPushMultFunction(lua_State* L, lua_CFunction fn);
	UEResult LuaPushDivFunction(lua_State* L, lua_CFunction fn);
	UEResult LuaPushNegaFunction(lua_State* L, lua_CFunction fn);
	UEResult LuaPushExpoFunction(lua_State* L, lua_CFunction fn);
	UEResult LuaPushConcatFunction(lua_State* L, lua_CFunction fn);

	UEResult LuaExecuteFile(lua_State* L, const std::string& filePath);
	UEResult LuaExecuteString(lua_State* L, const std::string& string);
}