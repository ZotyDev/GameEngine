#include "LuaAPI.h"

#include "Logger/Logger.h"

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
		lua_pushcclosure(m_LuaState, fn, 0);
		lua_setglobal(m_LuaState, fnName.c_str());
	}

	void LuaAPI::RegisterFunction(const std::string& fnName, lua_CFunction fn, void* userPtr)
	{
		lua_pushlightuserdata(m_LuaState, userPtr);
		lua_pushcclosure(m_LuaState, fn, 1);
		lua_setglobal(m_LuaState, fnName.c_str());
	}

	bool LuaAPI::CheckFunction(int msg)
	{
		if (msg != LUA_OK)
		{
			std::string errorMsg = lua_tostring(m_LuaState, -1);
			UE_LOG_ERROR(errorMsg);
			return false;
		}
		
		return true;
	}

	int LuaAPI::GetStackSize()
	{
		return lua_gettop(m_LuaState);
	}
}