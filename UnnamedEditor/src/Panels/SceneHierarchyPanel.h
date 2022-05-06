#pragma once

#include "Scene/Scene.h"

#include "PlatformIndependenceLayer/DynamicTree.h"

namespace UE
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel();

		void OnImGuiRender();

		Entity GetSelectedEntity() const { return m_SelectionContext; }
		void SetSelectedEntity(Entity entity);
	private:
		UEResult DrawEntityNode(DynamicTree<Entity>* self, DynamicTree<Entity>* branch);

	private:
		Entity m_SelectionContext;
		Ref<Scene> m_Scene;

		DynamicTree<Entity> m_EntityHierarchyAbstraction;
	};
}