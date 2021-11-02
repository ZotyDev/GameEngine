#include "uepch.h"
#include "ECS/Entity.h"

namespace UE
{
	EntityManager::EntityManager()
	{
		for (Entity e = 1; e <= UE_MAX_ENTITIES; e++)
		{
			m_AvaliableEntities.push(e);
		}
	}

	EntityManager::~EntityManager()
	{}

	UEResult EntityManager::CreateEntity(Entity& entity)
	{
		if (EntityCount == UE_MAX_ENTITIES)
		{
			UE_CORE_ERROR("Failed to create entity: reached max number of entities");
			return UEResult::Error;
		}

		entity = m_AvaliableEntities.front();
		m_AvaliableEntities.pop();

		return UEResult::Success;
	}

	UEResult EntityManager::RemoveEntity(Entity& entity)
	{
		if (entity > UE_MAX_ENTITIES || entity == UE_INVALID_ENTITY)
		{
			UE_CORE_ERROR("Failed to remove entity: invalid entity");
			return UEResult::Error;
		}

		m_AvaliableEntities.push(entity);
		entity = UE_INVALID_ENTITY;

		return UEResult::Success;
	}
}
