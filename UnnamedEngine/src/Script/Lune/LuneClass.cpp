#include "uepch.h"
#include "Script/Lune/LuneClass.h"

namespace UE
{
	LuneClass& LuneClass::Add(const UEString& name, lua_CFunction fn)
	{
		Functions.push_back(LuneFunction(name, fn));

		return *this;
	}

	LuneClass& LuneClass::Add(LuneClass cls)
	{
		Classes.push_back(cls);

		return *this;
	}

	LuneClass& LuneClass::AddCtor(const UEString& name, lua_CFunction ctor)
	{
		Ctors.push_back(LuneFunction(name, ctor));

		return *this;
	}

	LuneClass& LuneClass::SetDtor(lua_CFunction dtor)
	{
		Dtor = dtor;

		return *this;
	}

	void LuneClass::RegisterSelf(lua_State* L)
	{
		UE_LUA_TRACE("Dump from {0} start", Name);
		LuneStack(L).Dump();
		// Create new table current class
		lua_newtable(L);
		UEUint32 ClassIndex = lua_gettop(L);
		lua_pushvalue(L, ClassIndex);
		lua_setfield(L, -3, Name.c_str());

		// Register ctors
		UEUint32 CtorCount = Ctors.size();
		for (UEUint32 i = 0; i < CtorCount; i++)
		{
			Ctors[i].RegisterSelf(L, -2);
		}

		// Register class functions
		UEUint32 FunctionCount = Functions.size();
		for (UEUint32 i = 0; i < FunctionCount; i++)
		{
			Functions[i].RegisterSelf(L, -2);
		}

		// Register dtor
		UEUint32 MetatableIndex = lua_gettop(L);
		luaL_newmetatable(L, (Name + "Metatable").c_str());
		if (Dtor != nullptr)
		{
			lua_pushstring(L, "__gc");
			lua_pushcfunction(L, Dtor);
			lua_settable(L, -3);
		}

		// Register index
		lua_pushfstring(L, "__index");
		lua_pushvalue(L, ClassIndex);
		lua_settable(L, -3);

		lua_remove(L, MetatableIndex);
		
		// Register other classes
		UEUint32 ClassCount = Classes.size();
		for (UEUint32 i = 0; i < ClassCount; i++)
		{
			Classes[i].RegisterSelf(L);
		}

		lua_remove(L, ClassIndex);

		UE_LUA_TRACE("Dump from {0} end", Name);
		LuneStack(L).Dump();
		// Register current class table
		//lua_setfield(L, -2,Name.c_str());
	}
}