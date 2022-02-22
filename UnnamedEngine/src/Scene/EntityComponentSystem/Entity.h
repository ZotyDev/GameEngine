#pragma once

namespace UE
{
	typedef UEUint32 Entity;
	const Entity MaxEntities = 20000;

	class EntityManager
	{
	public:
		EntityManager();

		Entity CreateEntity();
		UEResult DestroyEntity(Entity entity);

		UEResult Each(const std::function<UEResult(Entity)>& f);

		UEUint32 Size() { return m_EntityCount; }

	private:
		std::queue<Entity> m_AvaliableEntitiesPool;
		UEUint32 m_EntityCount = 0;

		std::array<Entity, MaxEntities> m_ActiveEntityPool;

		std::unordered_map<Entity, UEUint32> m_EntityToIndexMap;
		std::unordered_map<UEUint32, Entity> m_IndexToEntityMap;
	};
}