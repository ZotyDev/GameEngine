#pragma once

#include "Script/Luna/LunaStack.h"

#include "Script/Luna/LunaFunction.h"

namespace UE
{
	class LunaModule
	{
	public:
		LunaModule(const UEString& name);
		~LunaModule();

		LunaModule& AddFunction(Ref<LunaFunction> function);

		UEResult Register(Ref<LunaStack> stack);

	private:
		UEString m_Name;
		std::vector<Ref<LunaFunction>> m_Functions;
	};
}