#pragma once

#include "Script/Lune/LuneClass.h"

namespace UE
{
	class LuneModule
	{
	public:
		LuneModule(const UEString& name)
			: Name(name)
		{}

		LuneModule& AddEnum(const UEString& name, UEUint16 value);
		LuneModule& AddEnum(const UEString& name, UEUint32 value);
		LuneModule& AddEnum(const UEString& name, UEUint64 value);
		LuneModule& AddFunction(const UEString& name, lua_CFunction fn);
		LuneModule& AddClass(LuneClass cls);
		LuneModule& AddClass(const UEString& name);
		LuneModule& AddModule(LuneModule mdl);
		LuneModule& AddModule(const UEString& name);

		void Register(lua_State* L, UEUint32 index);
		void RegisterSelf(Ref<LuneStack> stack);

		Ref<LuneClass> GetClass(const UEString& name);
		Ref<LuneModule> GetModule(const UEString& name);

		UEString Name;
		std::unordered_map<UEString, Ref<LuneEnum>> Enums;
		std::unordered_map<UEString, Ref<LuneFunction>> Functions;
		std::unordered_map<UEString, Ref<LuneClass>> Classes;
		std::unordered_map<UEString, Ref<LuneModule>> Modules;
	};
}