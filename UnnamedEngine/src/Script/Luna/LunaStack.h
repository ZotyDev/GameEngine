#pragma once

#include "Script/LuaAPI.h"

namespace UE
{
	class LunaStack
	{
	public:
		LunaStack();

		UEResult ExecuteLine(const UEString& line);
		UEResult ExecuteFile(const UEString& path);

		UEResult PushGlobalFunction(const UEString& name, lua_CFunction function);

		void Dump();

		lua_State* GetRawState() { return L; }

	private:
		lua_State* L;
	};
}