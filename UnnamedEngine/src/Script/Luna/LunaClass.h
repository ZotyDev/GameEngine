#pragma once

#include "Script/LuaAPI.h"

#include "Script/Luna/LunaStack.h"

namespace UE
{
	//template<typename T>
	class LunaClass
	{
	public:
		LunaClass(UEString name);
		~LunaClass();

		UEResult AddMethod(const UEString& name, lua_CFunction method);

	private:
		UEString m_Name;
		std::vector<luaL_Reg> m_Methods;
	};
}