#include "uepch.h"
#include "Scene/Scene.h"

namespace UE
{
	Scene::Scene()
	{
		m_EntityManager = CreateRef<EntityManager>();
		m_Name = "Unnamed Scene";
	}

	Scene::~Scene()
	{}

	Entity Scene::CreateEntity(const UEString& name)
	{
		return m_EntityManager->CreateEntity();
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_EntityManager->DestroyEntity(entity);
	}
}