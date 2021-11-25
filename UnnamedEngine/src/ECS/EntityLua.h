#pragma once

#include "Core/Base.h"

#include "Script/Lune/LuneAPI.h"

#include "ECS/Entity.h"

namespace UE
{
	static int lua_CreateEntity(lua_State* L)
	{
		// Create entity and push it into stack
		EntityManager* tEntityManager = (EntityManager*)lua_touserdata(L, lua_upvalueindex(1));
		Entity CurrentEntity;
		UEResult Result = tEntityManager->CreateEntity(CurrentEntity);
		if (Result == UEResult::Error)
		{
			UE_LUA_ERROR("Failed to create entity");
			return 0;
		}
		lua_newuserdata(L, sizeof(Entity));

		luaL_getmetatable(L, "EntityMetatable");
		lua_setmetatable(L, -2);

		return 1;
	}
}