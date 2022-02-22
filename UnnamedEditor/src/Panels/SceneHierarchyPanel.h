#pragma once

#include "Scene/Scene.h"

#include "Platform/DynamicTree.h"

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
		std::vector<Entity> m_EntityList;
		std::vector<Entity>::iterator m_aux_begin_iterator;
		std::vector<Entity>::iterator m_aux_traverse_iterator;
		std::vector<Entity>::iterator m_aux_end_iterator;
		std::vector<Entity>::iterator m_aux_moved_iterator;

		DynamicTree<Entity> m_Test;
	};
}