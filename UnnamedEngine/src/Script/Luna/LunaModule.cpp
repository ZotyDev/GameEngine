#include "uepch.h"
#include "Script/Luna/LunaModule.h"

namespace UE
{
	LunaModule::LunaModule(const UEString& name)
		: m_Name(name)
	{}

	LunaModule::~LunaModule()
	{}

	LunaModule& LunaModule::AddFunction(Ref<LunaFunction> function)
	{
		m_Functions.push_back(function);

		return *this;
	}

	UEResult LunaModule::Register(Ref<LunaStack> stack)
	{
		lua_State* L = stack->GetRawState();
		
		lua_newtable(L);
		UEUint32 ModuleIndex = lua_gettop(L);
		lua_pushvalue(L, ModuleIndex);
		lua_setglobal(L, m_Name.c_str());

		for (UEUint32 i = 0; i < m_Functions.size(); i++)
		{
			Ref<LunaFunction> CurrentFunction = m_Functions[i];
			lua_pushcfunction(L, CurrentFunction->GetFunction());
			lua_setfield(L, -2, CurrentFunction->GetName().c_str());
		}

		lua_pop(L, -1);

		return UEResult::Success;
	}
}