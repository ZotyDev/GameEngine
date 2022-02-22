#include "uepch.h"
#include "Scene/EntityComponentSystem/Entity.h"

namespace UE
{
	EntityManager::EntityManager()
	{
		for (UEUint64 i = 1; i < MaxEntities; i++)
		{
			m_AvaliableEntitiesPool.push(i);
		}
	}

	Entity EntityManager::CreateEntity()
	{
		if (m_ActiveEntityPool.size() > MaxEntities)
		{
			UE_CORE_ERROR("Failed to create entity: max number of entities reached");
			return 0;
		}

		// Get entity from avaliable pool
		Entity NewEntity = m_AvaliableEntitiesPool.front();
		m_AvaliableEntitiesPool.pop();

		// Put new entity at end and update the map
		UEUint32 NewIndex = m_EntityCount;
		m_EntityToIndexMap[NewEntity] = NewIndex;
		m_IndexToEntityMap[NewIndex] = NewEntity;
		m_ActiveEntityPool[NewIndex] = NewEntity;

		m_EntityCount++;

		return NewEntity;
	}

	UEResult EntityManager::DestroyEntity(Entity entity)
	{
		if (entity > MaxEntities)
		{
			UE_CORE_ERROR("Failed to destroy entity: value out of range (Expected value between: 0~{0} - Got {1})", MaxEntities, (UEUint64)entity);
			return UEResult::Error;
		}
		else if (m_EntityToIndexMap.find(entity) == m_EntityToIndexMap.end())
		{
			UE_CORE_ERROR("Failed to destroy entity: specified entity does not exist");
			return UEResult::Error;
		}

		// Return entity to avaliable pool
		m_AvaliableEntitiesPool.push(entity);

		// Copy entity at end into deleted element's place to maintain density
		UEUint32 IndexOfRemovedEntity = m_EntityToIndexMap[entity];
		UEUint32 IndexOfLastEntity = m_EntityCount - 1;
		m_ActiveEntityPool[IndexOfRemovedEntity] = m_ActiveEntityPool[IndexOfLastEntity];
		
		// Update map to point to moved spot
		Entity EntityOfLastElement = m_IndexToEntityMap[IndexOfLastEntity];
		m_EntityToIndexMap[EntityOfLastElement] = IndexOfRemovedEntity;
		m_IndexToEntityMap[IndexOfRemovedEntity] = EntityOfLastElement;

		m_EntityToIndexMap.erase(entity);
		m_IndexToEntityMap.erase(IndexOfLastEntity);

		m_EntityCount--;

		return UEResult::Success;
	}

	UEResult EntityManager::Each(const std::function<UEResult(Entity)>& f)
	{
		for (UEUint32 i = 0; i < m_EntityCount; i++)
		{
			Entity CurrentEntity = m_ActiveEntityPool[i];
			if (f(CurrentEntity) == UEResult::Error)
			{
				UE_CORE_INFO("Entity {0} failed to update: \"Each()\" returned ERROR", CurrentEntity);
				return UEResult::Error;
			}
		}
	}
}