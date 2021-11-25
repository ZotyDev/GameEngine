#pragma once

#include "Core/Base.h"

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#define LUNE_NONE			(-1)

#define LUNE_TNIL			0
#define LUNE_TBOOLEAN		1
#define LUNE_TLIGHUSERDATA	2
#define LUNE_TNUMBER		3
#define LUNE_TSTRING		4
#define LUNE_TTABLE			5
#define LUNE_TFUNCTION		6
#define LUNE_TUSERDATA		7
#define LUNE_TTHREAD		8
#define LUNE_TCTOR			9
#define LUNE_TDTOR			10
#define LUNE_TCLASS			11
#define LUNE_TMODULE		12
#define LUNE_TENUM			13

#define UE_LUAF(function, ...) LuneErrorCheck(L, function(L ,__VA_ARGS__))

namespace UE
{
	UEResult LuneErrorCheck(lua_State* L, int status);

	enum class LuneType
	{
		None				= LUNE_NONE,

		Nil					= LUNE_TNIL,
		Boolean				= LUNE_TBOOLEAN,
		LightUserdata		= LUNE_TLIGHUSERDATA,
		Number				= LUNE_TNUMBER,
		String				= LUNE_TSTRING,
		Table				= LUNE_TTABLE,
		Function			= LUNE_TFUNCTION,
		Userdata			= LUNE_TUSERDATA,
		Thread				= LUNE_TTHREAD,
		Ctor				= LUNE_TCTOR,
		Dtor				= LUNE_TDTOR,
		Class				= LUNE_TCLASS,
		Module				= LUNE_TMODULE,
		Enum				= LUNE_TENUM
	};

	class LuneStack
	{
	public:
		LuneStack()
		{
			L = luaL_newstate();
			luaL_openlibs(L);
		}

		LuneStack(lua_State* state)
		{
			L = state;
		}

		UEUint32 GetTop() { return lua_gettop(L); }

		void Dump();

		UEResult ExecuteLine(const UEString& line);
		UEResult ExecuteFile(const UEString& path);

		lua_State* L;
	};
}