#include "uepch.h"

#include "Script/Lune/LuneModule.h"

namespace UE
{
	LuneModule& LuneModule::Add(const UEString& name, lua_CFunction fn)
	{
		Functions.push_back(LuneFunction(name, fn));

		return *this;
	}

	LuneModule& LuneModule::Add(LuneClass cls)
	{
		Classes.push_back(cls);

		return *this;
	}

	LuneModule& LuneModule::Add(LuneModule mdl)
	{
		Modules.push_back(mdl);

		return *this;
	}

	void LuneModule::Register(LuneStack stack)
	{
		// Create new table
		lua_State* L = stack.L;

		UE_LUA_TRACE("Dump from {0} start", Name);
		LuneStack(L).Dump();

		lua_newtable(L);
		UEUint32 ModuleIndex = lua_gettop(L);
		lua_pushvalue(L, ModuleIndex);
		lua_setglobal(L, Name.c_str());

		// Register functions
		UEUint32 FunctionCount = Functions.size();
		for (UEUint32 i = 0; i < FunctionCount; i++)
		{
			Functions[i].RegisterSelf(L, -2);
		}

		// Register classes
		UEUint32 ClassCount = Classes.size();
		for (UEUint32 i = 0; i < ClassCount; i++)
		{
			Classes[i].RegisterSelf(L);
		}

		// Register modules
		UEUint32 ModuleCount = Modules.size();
		for (UEUint32 i = 0; i < ModuleCount; i++)
		{
			Modules[i].RegisterSelf(L);
		}

		lua_remove(L, ModuleIndex);

		UE_LUA_TRACE("Dump from {0} end", Name);
		LuneStack(L).Dump();
	}

	void LuneModule::RegisterSelf(lua_State* L)
	{
		UE_LUA_TRACE("Dump from {0} start", Name);
		LuneStack(L).Dump();

		// Create new table
		lua_newtable(L);
		UEUint32 ModuleIndex = lua_gettop(L);
		lua_pushvalue(L, ModuleIndex);
		lua_setfield(L, -3, Name.c_str());

		// Register functions
		UEUint32 FunctionCount = Functions.size();
		for (UEUint32 i = 0; i < FunctionCount; i++)
		{
			Functions[i].RegisterSelf(L, -2);
		}

		// Register classes
		UEUint32 ClassCount = Classes.size();
		for (UEUint32 i = 0; i < ClassCount; i++)
		{
			Classes[i].RegisterSelf(L);
		}

		// Register modules
		UEUint32 ModuleCount = Modules.size();
		for (UEUint32 i = 0; i < ModuleCount; i++)
		{
			Modules[i].RegisterSelf(L);
		}

		lua_remove(L, ModuleIndex);

		UE_LUA_TRACE("Dump from {0} end", Name);
		LuneStack(L).Dump();
	}
}