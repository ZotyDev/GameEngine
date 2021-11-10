#pragma once

#include "Core/Base.h"

#include "Script/Lune/LuneAPI.h"

#include "Core/Log.h"

namespace UE
{
	static int lua_CreateLogger(lua_State* L)
	{
		UEString name = luaL_checkstring(L, 1);

		// Create logger and push it into stack
		Log::CreateCustomLogger(name);
		Ref<spdlog::logger> RefToLogger = Log::GetCustomLogger(name);
		lua_pushlightuserdata(L, (void*)RefToLogger.get());

		luaL_getmetatable(L, "LoggerMetatable");
		lua_setmetatable(L, -2);
		return 1;
	}

	static int lua_GetLogger(lua_State* L)
	{
		UEString name = luaL_checkstring(L, 1);

		// Get logger and puhs in into stack
		Ref<spdlog::logger> RefToLogger = Log::GetCustomLogger(name);
		if (RefToLogger == nullptr)
		{
			UE_LUA_ERROR("Failed to get logger: {0} does not exist");
			return 0;
		}
		lua_pushlightuserdata(L, (void*)RefToLogger.get());

		luaL_getmetatable(L, "LoggerMetatable");
		lua_setmetatable(L, -2);
		return 1;
	}

	static int lua_LoggerTrace(lua_State* L)
	{
		spdlog::logger* LoggerPtr = (spdlog::logger*)lua_touserdata(L, 1);
		UEString msg = luaL_checkstring(L, 2);

		LoggerPtr->trace(msg);

		return 0;
	}

	static int lua_LoggerInfo(lua_State* L)
	{
		spdlog::logger* LoggerPtr = (spdlog::logger*)lua_touserdata(L, 1);
		UEString msg = luaL_checkstring(L, 2);

		LoggerPtr->info(msg);

		return 0;
	}

	static int lua_LoggerWarn(lua_State* L)
	{
		spdlog::logger* LoggerPtr = (spdlog::logger*)lua_touserdata(L, 1);
		UEString msg = luaL_checkstring(L, 2);

		LoggerPtr->warn(msg);

		return 0;
	}

	static int lua_LoggerError(lua_State* L)
	{
		spdlog::logger* LoggerPtr = (spdlog::logger*)lua_touserdata(L, 1);
		UEString msg = luaL_checkstring(L, 2);

		LoggerPtr->error(msg);

		return 0;
	}

	static int lua_LoggerCritical(lua_State* L)
	{
		spdlog::logger* LoggerPtr = (spdlog::logger*)lua_touserdata(L, 1);
		UEString msg = luaL_checkstring(L, 2);

		LoggerPtr->critical(msg);

		return 0;
	}
}