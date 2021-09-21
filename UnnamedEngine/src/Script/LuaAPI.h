#pragma once

#include "Script/LUA/LuaFunctionWrapper.h"

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

		static void ExecuteFile(const std::string& filePath);
		static void ExecuteString(const std::string& string);

		static lua_State* GetLua() { return m_LuaState; }
	private:
		static int GetStackSize();

	private:
		static lua_State* m_LuaState;
	};
}