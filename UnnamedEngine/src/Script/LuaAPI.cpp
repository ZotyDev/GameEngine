#include "uepch.h"
#include "LuaAPI.h"

namespace UE
{
	lua_State* LuaAPI::m_LuaState = nullptr;

	void LuaAPI::Init()
	{
		m_LuaState = luaL_newstate();
	}

	void LuaAPI::Shutdown()
	{
		lua_close(m_LuaState);
	}

	void LuaAPI::RegisterFunction(const std::string& fnName, lua_CFunction fn)
	{
		LuaRegisterFunction(m_LuaState, fnName, fn);
	}

	void LuaAPI::RegisterFunction(const std::string& fnName, lua_CFunction fn, void* userPtr)
	{
		LuaRegisterFunction(m_LuaState, fnName, fn, userPtr);
	}

	void LuaAPI::ExecuteFile(const std::string& filePath)
	{
		LuaExecuteFile(m_LuaState, filePath);
	}

	void LuaAPI::ExecuteString(const std::string& string)
	{
		LuaExecuteString(m_LuaState, string);
	}

	int LuaAPI::GetStackSize()
	{
		return lua_gettop(m_LuaState);
	}
}