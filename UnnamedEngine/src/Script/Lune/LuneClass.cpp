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

	void LuneClass::Register(lua_State* L, UEUint32 index)
	{
		//UE_LUA_TRACE("Dump from {0} start", Name);
		//LuneStack(L).Dump();

		// Create new table for current class
		lua_newtable(L);
		UEUint32 ClassIndex = lua_gettop(L);
		lua_pushvalue(L, ClassIndex);
		lua_setfield(L, index - 1, Name.c_str());

		// Register ctors
		UEUint32 CtorCount = Ctors.size();
		for (UEUint32 i = 0; i < CtorCount; i++)
		{
			Ctors[i].Register(L, -2);
		}

		// Register class functions
		UEUint32 FunctionCount = Functions.size();
		for (UEUint32 i = 0; i < FunctionCount; i++)
		{
			Functions[i].Register(L, -2);
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
		lua_pushstring(L, "__index");
		lua_pushvalue(L, ClassIndex);
		lua_settable(L, -3);

		lua_remove(L, MetatableIndex);

		// Register other classes
		UEUint32 ClassCount = Classes.size();
		for (UEUint32 i = 0; i < ClassCount; i++)
		{
			Classes[i].Register(L, -2);
		}

		lua_remove(L, ClassIndex);

		//UE_LUA_TRACE("Dump from {0} end", Name);
		//LuneStack(L).Dump();
	}

	void LuneClass::RegisterSelf(Ref<LuneStack> stack)
	{
		//UE_LUA_TRACE("Dump from {0} start", Name);
		//LuneStack(L).Dump();

		lua_State* L = stack->L;

		// Create new table for current class
		lua_newtable(L);
		UEUint32 ClassIndex = lua_gettop(L);
		lua_pushvalue(L, ClassIndex);
		lua_setglobal(L, Name.c_str());

		// Register ctors
		UEUint32 CtorCount = Ctors.size();
		for (UEUint32 i = 0; i < CtorCount; i++)
		{
			Ctors[i].Register(L, -2);
		}

		// Register class functions
		UEUint32 FunctionCount = Functions.size();
		for (UEUint32 i = 0; i < FunctionCount; i++)
		{
			Functions[i].Register(L, -2);
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
		lua_pushstring(L, "__index");
		lua_pushvalue(L, ClassIndex);
		lua_settable(L, -3);

		lua_remove(L, MetatableIndex);

		// Register other classes
		UEUint32 ClassCount = Classes.size();
		for (UEUint32 i = 0; i < ClassCount; i++)
		{
			Classes[i].Register(L, -2);
		}

		lua_remove(L, ClassIndex);

		//UE_LUA_TRACE("Dump from {0} end", Name);
		//LuneStack(L).Dump();
	}
}