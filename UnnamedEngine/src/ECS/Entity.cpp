#include "uepch.h"
#include "ECS/Entity.h"

namespace UE
{
	EntityManager::EntityManager()
		:m_EntityCount(0)
	{
		for (Entity entity = 0; entity < UE_MAX_ENTITIES; ++entity)
		{
			m_AvaliableEntities.push(entity);
		}
	}

	EntityManager::~EntityManager()
	{}

	UEResult EntityManager::CreateEntity(Entity& entity)
	{
		if (m_EntityCount > UE_MAX_ENTITIES)
		{
			UE_CORE_ERROR("Could not create entity with ID {0}: Maximun entity number reached");
			entity = 0;
			return UEResult::Error;
		}

		// Take ID from the front of the queue
		entity = m_AvaliableEntities.front();
		m_AvaliableEntities.pop();
		++m_EntityCount;

		return UEResult::Success;
	}

	UEResult EntityManager::DestroyEntity(Entity& entity)
	{
		if (entity > UE_MAX_ENTITIES)
		{
			UE_CORE_ERROR("Could not destroy entity with ID {0}: ID out of range");
			return UEResult::Error;
		}

		// Put the ID at the back of the queue
		m_AvaliableEntities.push(entity);
		entity = 0;
		--m_EntityCount;

		return UEResult::Success;
	}
}