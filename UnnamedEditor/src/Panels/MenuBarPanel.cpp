#include "uepch.h"
#include "Panels/MenuBarPanel.h"

#include <imgui.h>

#include "Panels/PanelsConfig.h"

namespace UE
{
	MenuBarPanel::MenuBarPanel()
	{}

	void MenuBarPanel::OnImGuiRender(Ref<Application::SharedData> data)
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New", "Ctrl+N"))
				{

				}

				if (ImGui::MenuItem("Open..", "Ctrl+O"))
				{

				}

				if (ImGui::MenuItem("Save", "Ctrl+S"))
				{

				}

				if (ImGui::MenuItem("Save As..", "Ctrl+Shift+S"))
				{

				}

				ImGui::Separator();

				if (ImGui::BeginMenu("Options"))
				{
					if (ImGui::MenuItem("Maximize on play", NULL, &PanelsConfig::MaximizeOnPlay))
					{

					}

					ImGui::EndMenu();
				}

				ImGui::Separator();

				if (ImGui::MenuItem("Exit", "Alt+F4"))
				{
					data->m_Running = false;
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("View"))
			{
				if (ImGui::MenuItem("Viewport", NULL, &PanelsShowConfig::ShowViewport))
				{

				}

				if (ImGui::MenuItem("ContentBrowser", NULL, &PanelsShowConfig::ShowContentBrowser))
				{

				}

				if (ImGui::MenuItem("Properties", NULL, &PanelsShowConfig::ShowProperties))
				{

				}

				if (ImGui::MenuItem("Scene Hierarchy", NULL, &PanelsShowConfig::ShowSceneHierarchy))
				{

				}

				if (ImGui::MenuItem("Profiler", NULL, &PanelsShowConfig::ShowProfiler))
				{

				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Game"))
			{
				if (ImGui::MenuItem("Play", !PanelsConfig::ProjectRunning ? "F9" : NULL, nullptr, !PanelsConfig::ProjectRunning))
				{
					if (PanelsConfig::MaximizeOnPlay)
					{
					}

					PanelsConfig::ProjectRunning = true;
				}

				if (ImGui::MenuItem("Stop", PanelsConfig::ProjectRunning? "F9" : NULL, nullptr, PanelsConfig::ProjectRunning))
				{
					PanelsConfig::ProjectRunning = false;
					PanelsConfig::ProjectPaused = false;
				}

				if (ImGui::MenuItem("Pause", NULL, nullptr, !PanelsConfig::ProjectPaused && PanelsConfig::ProjectRunning))
				{
					PanelsConfig::ProjectPaused = true;
				}

				if (ImGui::MenuItem("Resume", NULL, nullptr, PanelsConfig::ProjectPaused))
				{
					PanelsConfig::ProjectPaused = false;
				}

				ImGui::Separator();

				if (ImGui::MenuItem("Hot Reload", "F5", nullptr, PanelsConfig::ProjectRunning))
				{

				}

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
	}
}