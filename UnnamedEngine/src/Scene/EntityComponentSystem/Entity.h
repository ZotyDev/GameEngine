#pragma once

namespace UE
{
	typedef UEUint64 Entity;
	const Entity MaxEntities = 20000;
	const Entity InvalidEntity = 0;

	class EntityManager
	{
	public:
		EntityManager();

		UEResult<Entity> CreateEntity();
		UEResult<> DestroyEntity(Entity entity);

		UEResult<> Each(const std::function<UEResult<>(Entity)>& f);

		UEUint64 Size() { return m_EntityCount; }

	private:
		std::queue<Entity> m_AvaliableEntitiesPool;
		UEUint64 m_EntityCount = 0;

		std::array<Entity, MaxEntities> m_ActiveEntityPool;

		std::unordered_map<Entity, UEUint64> m_EntityToIndexMap;
		std::unordered_map<UEUint64, Entity> m_IndexToEntityMap;
	};
}