#pragma once

#include "Core/Base.h"

#include "Script/LuaAPI.h"

#include "Math/Easing/Easing.h"

namespace UE
{
	static int lua_EaseInBack(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseInBack(arg1));

		return 1;
	}

	static int lua_EaseOutBack(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseOutBack(arg1));

		return 1;
	}

	static int lua_EaseInOutBack(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseInOutBack(arg1));

		return 1;
	}

	static int lua_EaseInBounce(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseInBounce(arg1));

		return 1;
	}

	static int lua_EaseOutBounce(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseOutBounce(arg1));

		return 1;
	}

	static int lua_EaseInOutBounce(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseInOutBounce(arg1));

		return 1;
	}

	static int lua_EaseInCirc(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseInCirc(arg1));

		return 1;
	}

	static int lua_EaseOutCirc(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseOutCirc(arg1));

		return 1;
	}

	static int lua_EaseInOutCirc(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseInOutCirc(arg1));

		return 1;
	}

	static int lua_EaseInCubic(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseInCubic(arg1));

		return 1;
	}

	static int lua_EaseOutCubic(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseOutCubic(arg1));

		return 1;
	}

	static int lua_EaseInOutCubic(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseInOutCubic(arg1));

		return 1;
	}

	static int lua_EaseInElastic(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseInElastic(arg1));

		return 1;
	}

	static int lua_EaseOutElastic(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseOutElastic(arg1));

		return 1;
	}

	static int lua_EaseInOutElastic(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseInOutElastic(arg1));

		return 1;
	}

	static int lua_EaseInExpo(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseInExpo(arg1));

		return 1;
	}

	static int lua_EaseOutExpo(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseOutExpo(arg1));

		return 1;
	}

	static int lua_EaseInOutExpo(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseInOutExpo(arg1));

		return 1;
	}

	static int lua_EaseInQuad(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseInQuad(arg1));

		return 1;
	}

	static int lua_EaseOutQuad(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseOutQuad(arg1));

		return 1;
	}

	static int lua_EaseInOutQuad(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseInOutQuad(arg1));

		return 1;
	}

	static int lua_EaseInQuart(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseInQuart(arg1));

		return 1;
	}

	static int lua_EaseOutQuart(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseOutQuart(arg1));

		return 1;
	}

	static int lua_EaseInOutQuart(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseInOutQuart(arg1));

		return 1;
	}

	static int lua_EaseInQuint(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseInQuint(arg1));

		return 1;
	}

	static int lua_EaseOutQuint(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseOutQuint(arg1));

		return 1;
	}

	static int lua_EaseInOutQuint(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseInOutQuint(arg1));

		return 1;
	}

	static int lua_EaseInSine(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseInSine(arg1));

		return 1;
	}

	static int lua_EaseOutSine(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseOutSine(arg1));

		return 1;
	}

	static int lua_EaseInOutSine(lua_State* L)
	{
		UEDouble arg1 = luaL_checknumber(L, 1);
		lua_pushnumber(L, EaseInOutSine(arg1));

		return 1;
	}

}