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

		LuneModule& Add(const UEString& name, UEUint16 value);
		LuneModule& Add(const UEString& name, UEUint32 value);
		LuneModule& Add(const UEString& name, UEUint64 value);
		LuneModule& Add(const UEString& name, lua_CFunction fn);
		LuneModule& Add(LuneClass cls);
		LuneModule& Add(LuneModule mdl);

		void Register(LuneStack stack);
		void RegisterSelf(lua_State* L);

		UEString Name;
		std::vector<LuneFunction> Functions;
		std::vector<LuneClass> Classes;
		std::vector<LuneModule> Modules;
		std::vector<LuneEnum> Enums;
	};
}