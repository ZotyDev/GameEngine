#pragma once

#include "Script/Luna/LunaStack.h"

namespace UE
{
	class LunaFunction
	{
	public:
		LunaFunction(const UEString& name, lua_CFunction function);

		LunaFunction& Register(Ref<LunaStack> stack, UEResult& result);

		lua_CFunction GetFunction() { return m_Function; }
		UEString GetName() { return m_Name; }

	private:
		lua_CFunction m_Function;
		UEString m_Name;
	};
}