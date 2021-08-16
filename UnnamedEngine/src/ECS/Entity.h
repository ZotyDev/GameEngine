#pragma once

#define UE_INVALID_ENTITY 0

#include <queue>

namespace UE
{
	// 0 as ID represents a invalid Entity
	using Entity = uint64_t;

	const Entity UE_MAX_ENTITIES = 4000;

	class EntityManager
	{
	public:
		EntityManager();
		~EntityManager();

		UEResult CreateEntity(Entity& entity);
		UEResult DestroyEntity(Entity& entity);

		uint64_t GetEntityCount() { return m_EntityCount; }
	private:
		// Unused entity IDs
		std::queue<Entity> m_AvaliableEntities;

		uint64_t m_EntityCount;
	};
}