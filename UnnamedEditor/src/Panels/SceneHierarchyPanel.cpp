#include "uepch.h"
#include "Panels/SceneHierarchyPanel.h"

#include <imgui.h>

#include "Panels/PanelsConfig.h"

namespace UE
{
	SceneHierarchyPanel::SceneHierarchyPanel()
	{}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		if (PanelsShowConfig::ShowSceneHierarchy && !(PanelsConfig::MaximizeOnPlay && PanelsConfig::ProjectRunning))
		{
			ImGui::Begin("Scene Hierarchy");

			ImGui::End();
		}
	}
}