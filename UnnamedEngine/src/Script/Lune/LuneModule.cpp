#include "uepch.h"

#include "Script/Lune/LuneModule.h"

namespace UE
{
	LuneModule& LuneModule::AddEnum(const UEString& name, UEUint16 value)
	{
		std::unordered_map<UEString, Ref<LuneEnum>>::iterator it = Enums.find(name);
		std::unordered_map<UEString, Ref<LuneEnum>>::const_iterator end = Enums.end();
		if (it == end)
		{
			Enums.insert({ name, CreateRef<LuneEnum>(name, value) });
		}
		else
		{
			UE_LUA_ERROR("Failed to register \"{0}\" enum: already registered", name);
		}

		return *this;
	}

	LuneModule& LuneModule::AddEnum(const UEString& name, UEUint32 value)
	{
		std::unordered_map<UEString, Ref<LuneEnum>>::iterator it = Enums.find(name);
		std::unordered_map<UEString, Ref<LuneEnum>>::const_iterator end = Enums.end();
		if (it == end)
		{
			Enums.insert({ name, CreateRef<LuneEnum>(name, value) });
		}
		else
		{
			UE_LUA_ERROR("Failed to register \"{0}\" enum: already registered", name);
		}

		return *this;
	}

	LuneModule& LuneModule::AddEnum(const UEString& name, UEUint64 value)
	{
		std::unordered_map<UEString, Ref<LuneEnum>>::iterator it = Enums.find(name);
		std::unordered_map<UEString, Ref<LuneEnum>>::const_iterator end = Enums.end();
		if (it == end)
		{
			Enums.insert({ name, CreateRef<LuneEnum>(name, value) });
		}
		else
		{
			UE_LUA_ERROR("Failed to register \"{0}\" enum: already registered", name);
		}

		return *this;
	}

	LuneModule& LuneModule::AddFunction(const UEString& name, lua_CFunction fn)
	{
		std::unordered_map<UEString, Ref<LuneFunction>>::iterator it = Functions.find(name);
		std::unordered_map<UEString, Ref<LuneFunction>>::const_iterator end = Functions.end();
		if (it == end)
		{
			Functions.insert({ name, CreateRef<LuneFunction>(name, fn) });
		}
		else
		{
			UE_LUA_ERROR("Failed to register \"{0}\" function: already registered", name);
		}

		return *this;
	}

	LuneModule& LuneModule::AddClass(LuneClass cls)
	{
		std::unordered_map<UEString, Ref<LuneClass>>::iterator it = Classes.find(cls.Name);
		std::unordered_map<UEString, Ref<LuneClass>>::const_iterator end = Classes.end();
		if (it == end)
		{
			Classes.insert({ cls.Name, CreateRef<LuneClass>(cls)});
		}
		else
		{
			UE_LUA_ERROR("Failed to register \"{0}\" class: already registered", cls.Name);
		}

		return *this;
	}

	LuneModule& LuneModule::AddClass(const UEString& name)
	{
		std::unordered_map<UEString, Ref<LuneClass>>::iterator it = Classes.find(name);
		std::unordered_map<UEString, Ref<LuneClass>>::const_iterator end = Classes.end();
		if (it == end)
		{
			Classes.insert({ name, CreateRef<LuneClass>(name) });
		}
		else
		{
			UE_LUA_ERROR("Failed to register \"{0}\" class: already registered", name);
		}

		return *this;
	}

	LuneModule& LuneModule::AddModule(LuneModule mdl)
	{
		std::unordered_map<UEString, Ref<LuneModule>>::iterator it = Modules.find(mdl.Name);
		std::unordered_map<UEString, Ref<LuneModule>>::const_iterator end = Modules.end();
		if (it == end)
		{
			Modules.insert({ mdl.Name, CreateRef<LuneModule>(mdl) });
		}
		else
		{
			UE_LUA_ERROR("Failed to register \"{0}\" module: already registered", mdl.Name);
		}

		return *this;
	}

	LuneModule& LuneModule::AddModule(const UEString& name)
	{
		std::unordered_map<UEString, Ref<LuneModule>>::iterator it = Modules.find(name);
		std::unordered_map<UEString, Ref<LuneModule>>::const_iterator end = Modules.end();
		if (it == end)
		{
			Modules.insert({ name, CreateRef<LuneModule>(name) });
		}
		else
		{
			UE_LUA_ERROR("Failed to register \"{0}\" module: already registered", name);
		}

		return *this;
	}

	Ref<LuneClass> LuneModule::GetClass(const UEString& name)
	{
		std::unordered_map<UEString, Ref<LuneClass>>::iterator it = Classes.find(name);
		std::unordered_map<UEString, Ref<LuneClass>>::const_iterator end = Classes.end();
		if (it != end)
		{
			return it->second;
		}
		else
		{
			UE_LUA_ERROR("Could not find \"{0}\" class");
			return nullptr;
		}
	}

	Ref<LuneModule> LuneModule::GetModule(const UEString& name)
	{
		std::unordered_map<UEString, Ref<LuneModule>>::iterator it = Modules.find(name);
		std::unordered_map<UEString, Ref<LuneModule>>::const_iterator end = Modules.end();
		if (it != end)
		{
			return it->second;
		}
		else
		{
			UE_LUA_ERROR("Could not find \"{0}\" module");
			return nullptr;
		}
	}

	void LuneModule::Register(lua_State* L, UEUint32 index)
	{
		//UE_LUA_TRACE("Dump from {0} start", Name);
		//LuneStack(L).Dump();

		// Create new table
		lua_newtable(L);
		UEUint32 ModuleIndex = lua_gettop(L);
		lua_pushvalue(L, ModuleIndex);
		lua_setfield(L, index - 1, Name.c_str());

		// Register enums
		for (auto& it: Enums)
		{
			it.second->Register(L, -2);
		}

		// Register functions
		for (auto& it: Functions)
		{
			it.second->Register(L, -2);
		}

		// Register classes
		for (auto& it: Classes)
		{
			it.second->Register(L, -2);
		}

		// Register modules
		for (auto& it: Modules)
		{
			it.second->Register(L, -2);
		}

		lua_remove(L, ModuleIndex);

		//UE_LUA_TRACE("Dump from {0} end", Name);
		//LuneStack(L).Dump();
	}

	void LuneModule::RegisterSelf(Ref<LuneStack> stack)
	{
		//UE_LUA_TRACE("Dump from {0} start", Name);
		//LuneStack(L).Dump();

		lua_State* L = stack->L;

		// Create new table
		lua_newtable(L);
		UEUint32 ModuleIndex = lua_gettop(L);
		lua_pushvalue(L, ModuleIndex);
		lua_setglobal(L, Name.c_str());

		// Register enums
		for (auto& it : Enums)
		{
			it.second->Register(L, -2);
		}

		// Register functions
		for (auto& it : Functions)
		{
			it.second->Register(L, -2);
		}

		// Register classes
		for (auto& it : Classes)
		{
			it.second->Register(L, -2);
		}

		// Register modules
		for (auto& it : Modules)
		{
			it.second->Register(L, -2);
		}

		lua_remove(L, ModuleIndex);

		//UE_LUA_TRACE("Dump from {0} end", Name);
		//LuneStack(L).Dump();
	}
}