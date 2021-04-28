#pragma once

#include "Core/Base.h"

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

namespace UE
{
	class LuaAPI 
	{
	public:
		static void Init();
		static void Shutdown();

		// Lua C function always return int, the value is the number of arguments returned by the functionn
		static void RegisterFunction(const std::string& fnName, lua_CFunction fn);
		static void RegisterFunction(const std::string& fnName, lua_CFunction fn, void* userPtr);

		static int ExecuteFile(const std::string& filePath);

	private:
		static bool CheckFunction(int msg);
		static int GetStackSize();

	private:
		static lua_State* m_LuaState;
	};
}