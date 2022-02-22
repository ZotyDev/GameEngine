#include "uepch.h"
#include "Panels/SceneHierarchyPanel.h"

#include <imgui.h>

#include "Panels/PanelsConfig.h"

namespace UE
{
	SceneHierarchyPanel::SceneHierarchyPanel()
	{
		m_Scene = CreateRef<Scene>();
		m_Test = DynamicTree<Entity>(0);

		for (UEUint32 i = 0; i < 2; i++)
		{
			DynamicTree<Entity> NewNode(m_Scene->CreateEntity());
			m_Test.PushBack(NewNode);
		}

		m_Test.SetEachFn(std::bind(&SceneHierarchyPanel::DrawEntityNode, this, std::placeholders::_1, std::placeholders::_2));
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		if (PanelsShowConfig::ShowSceneHierarchy && !(PanelsConfig::MaximizeOnPlay && PanelsConfig::ProjectRunning))
		{
			ImGui::Begin("Scene Hierarchy");

			m_aux_begin_iterator = m_EntityList.begin();
			m_aux_end_iterator = m_EntityList.end();
			m_aux_traverse_iterator = m_aux_begin_iterator;
			//while (m_aux_traverse_iterator != m_aux_end_iterator)
			//{
			//	DrawEntityNode();
			//}

			m_Test.Each();

			// Left-click on blank space
			if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			{
				m_SelectionContext = {};
			}

			// Right-click on blank space
			if (ImGui::BeginPopupContextWindow(0, 1, false))
			{
				if (ImGui::BeginMenu("Create"))
				{
					if (ImGui::MenuItem("Empty Entity"))
					{
						Entity CreatedEntity = m_Scene->CreateEntity();
						//m_EntityList.push_back(CreatedEntity);
						m_Test.PushBack(DynamicTree<Entity>(CreatedEntity));
					} // Empty Entity

					if (ImGui::MenuItem("Camera"))
					{

					} // Camera

					if (ImGui::MenuItem("Text"))
					{

					} // Text

					if (ImGui::BeginMenu("2D"))
					{
						if (ImGui::MenuItem("Quad"))
						{

						} // Quad

						if (ImGui::MenuItem("Circle"))
						{

						} // Circle

						if (ImGui::MenuItem("Hexagon"))
						{

						} // Hexagon

						ImGui::EndMenu();
					} // 2D

					if (ImGui::BeginMenu("3D"))
					{
						if (ImGui::MenuItem("Cube"))
						{

						} // Cube

						if (ImGui::MenuItem("Sphere"))
						{

						} // Sphere

						if (ImGui::MenuItem("Capsule"))
						{

						} // Capsule

						if (ImGui::MenuItem("Cylinder"))
						{

						} // Cylinder

						if (ImGui::MenuItem("Torus"))
						{

						} // Torus

						if (ImGui::MenuItem("Plane"))
						{

						} // Plane

						if (ImGui::MenuItem("Cone"))
						{

						} // Cone

						if (ImGui::MenuItem("Pyramid"))
						{

						} // Pyramid

						ImGui::EndMenu();
					} // 3D

					ImGui::Separator();

					if (ImGui::MenuItem("Directional Light"))
					{

					} // Directional Light

					if (ImGui::MenuItem("Point Light"))
					{

					} // Direction Light

					if (ImGui::MenuItem("Sky Light"))
					{

					} // Sky Light

					ImGui::Separator();

					if (ImGui::MenuItem("Sound Source"))
					{

					} // Sound Source

					if (ImGui::MenuItem("Sound Listener"))
					{

					} // Sound Listener

					ImGui::EndMenu();
				} // Create

				ImGui::EndPopup();
			}

			ImGui::End();
		}
	}

	void SceneHierarchyPanel::SetSelectedEntity(Entity entity)
	{
		m_SelectionContext = entity;
	}

	UEResult SceneHierarchyPanel::DrawEntityNode(DynamicTree<Entity>* self, DynamicTree<Entity>* branch)
	{
		Entity CurrentEntity = branch->Element;
		UEUint32 CurrentEntityIndex = self->GetTraverseIndex();

		UEBool Empty = branch->Size() == 0;

		UEBool EntityDeleted = false;
		UEBool Opened = false;

		UEString EntityDisplayName = "Empty Entity " + std::to_string(CurrentEntity);

		ImGuiTreeNodeFlags Flags = ((m_SelectionContext == CurrentEntity) ? ImGuiTreeNodeFlags_Selected : 0) | (Empty ? ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_OpenOnArrow);
		Flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });
		Opened = ImGui::TreeNodeEx((void*)(UEUint32)CurrentEntity, Flags, EntityDisplayName.c_str());
		ImGui::PopStyleVar();

		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = CurrentEntity;
		}

		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
			{
				EntityDeleted = true;
			}

			ImGui::EndPopup();
		}

		if (ImGui::BeginDragDropSource())
		{
			ImGui::SetDragDropPayload("ENTITY", (void*)&CurrentEntityIndex, sizeof(UEUint32));

			ImGui::Text(EntityDisplayName.c_str());

			ImGui::EndDragDropSource();
		}

		if (Opened)
		{
			//branch->Each();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });
		ImGui::InvisibleButton(" ", ImVec2(-1, 3));
		ImGui::PopStyleVar();

		if (ImGui::BeginDragDropTargetInBetween())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayloadInBetween("ENTITY"))
			{
				UEUint32 MovedEntityIndex = *(UEUint32*)payload->Data;

				self->OrderedSwap(CurrentEntityIndex + 1, MovedEntityIndex);

			}
			ImGui::EndDragDropTarget();
		}

		if (Opened)
		{
			ImGui::TreePop();
		}

		if (EntityDeleted)
		{
			m_Scene->DestroyEntity(CurrentEntity);
			if (m_SelectionContext == CurrentEntity)
			{
				m_SelectionContext = {};
			}

			self->EraseAtTraverse();
		}

		return UEResult::Success;
	}

	//void SceneHierarchyPanel::DrawEntityNode()
	//{
	//	Entity CurrentEntity = *m_aux_traverse_iterator;

	//	UEBool Opened = false;
	//	UEBool EntityDeleted = false;
	//	UEBool Empty = true;
	//	UEBool ShouldIncrement = true;

	//	UEString EntityDisplayName = "Empty Entity " + std::to_string(CurrentEntity);

	//	ImGuiTreeNodeFlags Flags = ((m_SelectionContext == CurrentEntity) ? ImGuiTreeNodeFlags_Selected : 0) | (Empty ? ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_OpenOnArrow);
	//	Flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

	//	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });
	//	Opened = ImGui::TreeNodeEx((void*)(UEUint32)CurrentEntity, Flags, EntityDisplayName.c_str());
	//	ImGui::PopStyleVar();

	//	if (ImGui::BeginDragDropTarget())
	//	{
	//		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayloadSmall("ENTITY"))
	//		{
	//			UEUint32 CurrentEntityIndex = m_aux_traverse_iterator - m_aux_begin_iterator;
	//			UEUint32 MovedEntityIndex = m_aux_moved_iterator - m_aux_begin_iterator;

	//			// Remove entity from list
	//			m_EntityList.erase(m_aux_moved_iterator);

	//			// Check if index should be updated
	//			if (MovedEntityIndex < CurrentEntityIndex)
	//			{
	//				CurrentEntityIndex--;
	//			}

	//			// Update iterators
	//			m_aux_begin_iterator = m_EntityList.begin();
	//			m_aux_end_iterator = m_EntityList.end();
	//			m_aux_traverse_iterator = (m_EntityList.begin() + CurrentEntityIndex);
	//		}
	//		ImGui::EndDragDropTarget();
	//	}

	//	if (ImGui::IsItemClicked())
	//	{
	//		m_SelectionContext = CurrentEntity;
	//	}

	//	if (ImGui::BeginPopupContextItem())
	//	{
	//		if (ImGui::MenuItem("Delete Entity"))
	//		{
	//			EntityDeleted = true;
	//		}

	//		ImGui::EndPopup();
	//	}

	//	if (ImGui::BeginDragDropSource())
	//	{
	//		ImGui::SetDragDropPayload("ENTITY", nullptr, 0);
	//		
	//		m_aux_moved_iterator = m_aux_traverse_iterator;
	//		ImGui::Text(EntityDisplayName.c_str());

	//		ImGui::EndDragDropSource();
	//	}

	//	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });
	//	ImGui::InvisibleButton(" ", ImVec2(-1, 3));
	//	ImGui::PopStyleVar();

	//	if (ImGui::BeginDragDropTargetInBetween())
	//	{
	//		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayloadInBetween("ENTITY"))
	//		{
	//			UEUint32 CurrentEntityIndex = m_aux_traverse_iterator - m_aux_begin_iterator;
	//			UEUint32 MovedEntityIndex = m_aux_moved_iterator - m_aux_begin_iterator;
	//			
	//			// Change position of entity and mantain order of vector
	//			if (CurrentEntityIndex < MovedEntityIndex)
	//			{
	//				// Rotate by 1 to left the range between current entity and moved entity
	//				std::rotate(m_aux_traverse_iterator + 1, m_aux_moved_iterator, m_aux_moved_iterator + 1);
	//			}
	//			else
	//			{
	//				// What the fuck did you just bring upon this cursed land?
	//				// Rotate by 1 to right the range between current entity and moved entity
	//				std::rotate(m_EntityList.rend() - CurrentEntityIndex - 1, m_EntityList.rend() - MovedEntityIndex - 1, m_EntityList.rend() - MovedEntityIndex);
	//			}

	//		}
	//		ImGui::EndDragDropTarget();
	//	}

	//	if (Opened)
	//	{
	//		ImGui::TreePop();
	//	}

	//	if (EntityDeleted)
	//	{
	//		m_Scene->DestroyEntity(CurrentEntity);
	//		if (m_SelectionContext == CurrentEntity)
	//		{
	//			m_SelectionContext = {};
	//		}

	//		m_aux_traverse_iterator = m_EntityList.erase(m_aux_traverse_iterator);
	//		m_aux_end_iterator = m_EntityList.end();

	//		ShouldIncrement = false;
	//	}
	//
	//	if (ShouldIncrement)
	//	{
	//		m_aux_traverse_iterator++;
	//	}
	//}
}