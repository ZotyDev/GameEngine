#include "uepch.h"
#include "Script/Luna/LunaFunction.h"

namespace UE
{
	LunaFunction::LunaFunction(const UEString& name, lua_CFunction function)
		: m_Name(name), m_Function(function)
	{}

	LunaFunction& LunaFunction::Register(Ref<LunaStack> stack, UEResult& result)
	{
		result = stack->PushGlobalFunction(m_Name, m_Function);

		return *this;
	}
}