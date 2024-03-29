#pragma once

#include "Script/Lune/LuneFunction.h"
#include "Script/Lune/LuneEnum.h"

namespace UE
{
	class LuneClass
	{
	public:
		LuneClass(const UEString& name)
			: Name(name)
		{}

		LuneClass& Add(const UEString& name, lua_CFunction fn);
		LuneClass& Add(LuneClass cls);
		LuneClass& AddCtor(const UEString& name, lua_CFunction ctor);
		LuneClass& SetDtor(lua_CFunction dtor);

		void Register(lua_State* L, UEUint32 index);
		void RegisterSelf(Ref<LuneStack> stack);

		UEString Name;
		std::vector<LuneFunction> Ctors;
		lua_CFunction Dtor = nullptr;
		std::vector<LuneFunction> Functions;
		std::vector<LuneClass> Classes;
	};
}