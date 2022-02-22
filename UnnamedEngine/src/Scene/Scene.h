#pragma once

#include "Scene/EntityComponentSystem/Entity.h"

namespace UE
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const UEString& name = UEString());
		void DestroyEntity(Entity entity);

		Ref<EntityManager> GetEntityManager() const { return m_EntityManager; }

	private:
		Ref<EntityManager> m_EntityManager;
	};
}