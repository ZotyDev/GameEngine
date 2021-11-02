#pragma once

#define UE_INVALID_ENTITY	0
#define UE_MAX_ENTITIES		8196

namespace UE
{
	// 0 as ID represents a invalid Entity
	using Entity = UEUint32;

	class EntityManager
	{
	public:
		EntityManager();
		~EntityManager();

		UEResult CreateEntity(Entity& entity);
		UEResult RemoveEntity(Entity& entity);

	private:
		std::queue<Entity> m_AvaliableEntities;
		Entity EntityCount = 0;
	};
}
