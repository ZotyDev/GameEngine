#include "uepch.h"
#include "Panels/MenuBarPanel.h"

#include <imgui.h>

#include "ProjectConfig.h"

#include "Panels/PanelsConfig.h"

namespace UE
{
	MenuBarPanel::MenuBarPanel()
	{}

	UEBool NewProjectPopupTemp = false;
	UEBool OpenProjectPopupTemp = false;
	UEBool ProjectInfoPopupTemp = false;

	char ProjectNameBuffer[256] = "";
	char ProjectLocationBuffer[256] = "";

	void MenuBarPanel::OnImGuiRender(Ref<Application::SharedData> data)
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New", "Ctrl+N"))
				{
					NewProjectPopupTemp = true;
				}

				if (ImGui::MenuItem("Open..", "Ctrl+O"))
				{
					OpenProjectPopupTemp = true;
				}

				if (ImGui::MenuItem("Save", "Ctrl+S"))
				{

				}

				if (ImGui::MenuItem("Save As..", "Ctrl+Shift+S"))
				{

				}

				ImGui::Separator();

				if (ImGui::MenuItem("Project Info"))
				{
					ProjectInfoPopupTemp = true;
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
				if (ImGui::MenuItem("Viewport", NULL, &ActivePanelsConfig::Viewport))
				{

				}

				if (ImGui::MenuItem("ContentBrowser", NULL, &ActivePanelsConfig::ContentBrowser))
				{

				}

				if (ImGui::MenuItem("Properties", NULL, &ActivePanelsConfig::Properties))
				{

				}

				if (ImGui::MenuItem("Scene Hierarchy", NULL, &ActivePanelsConfig::SceneHierarchy))
				{

				}

				if (ImGui::MenuItem("Profiler", NULL, &ActivePanelsConfig::Profiler))
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

		if (NewProjectPopupTemp == true)
		{
			ImGui::OpenPopup("New Project");
			NewProjectPopupTemp = false;
		}
		
		if (OpenProjectPopupTemp == true)
		{
			ImGui::OpenPopup("Open Project");
			OpenProjectPopupTemp = false;
		}

		if (ProjectInfoPopupTemp == true)
		{
			ImGui::OpenPopup("Project Info");
			ProjectInfoPopupTemp = false;
		}


		// Always center this window when appearing
		ImVec2 center = ImGui::GetMainViewport()->GetCenter();
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

		if (ImGui::BeginPopupModal("New Project", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("Project Name:");
			ImGui::InputText("##ProjectName", ProjectNameBuffer, 256);

			ImGui::Text("Project Location:");
			
			ImGui::InputText("##ProjectLocation", ProjectLocationBuffer, 256);
			ImGui::SameLine();
			if (ImGui::Button("Browse"))
			{
				UEPath TempPathHolder;
				if (FileSystem::FileSelectorDialog(TempPathHolder, {}, false))
				{
					std::strcpy(ProjectLocationBuffer, TempPathHolder.string().c_str());
				}
			}

			if (ImGui::Button("Create", ImVec2(120, 0))) 
			{
				ProjectConfig::ProjectName = ProjectNameBuffer;
				ProjectConfig::ProjectLocation = ProjectLocationBuffer;
				ProjectConfig::AssetPath = ProjectConfig::ProjectLocation.string() + "/assets";
				ProjectConfig::CurrentDirectory = ProjectConfig::AssetPath;

				ImGui::CloseCurrentPopup(); 
			}
			
			ImGui::SetItemDefaultFocus();
			ImGui::SameLine();
			
			if (ImGui::Button("Cancel", ImVec2(120, 0))) 
			{ 
				ImGui::CloseCurrentPopup(); 
			}

			ImGui::EndPopup();
		}

		// Always center this window when appearing
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
		if (ImGui::BeginPopupModal("Open Project", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{

			ImGui::Text("Project Location:");
			ImGui::InputText("##ProjectLocation", ProjectLocationBuffer, 256);

			if (ImGui::Button("Open", ImVec2(120, 0)))
			{
				ProjectConfig::ProjectLocation = ProjectLocationBuffer;
				ProjectConfig::AssetPath = ProjectConfig::ProjectLocation.string() + "/assets";
				ProjectConfig::CurrentDirectory = ProjectConfig::AssetPath;

				ImGui::CloseCurrentPopup();
			}

			ImGui::SetItemDefaultFocus();
			ImGui::SameLine();

			if (ImGui::Button("Cancel", ImVec2(120, 0)))
			{
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		// Always center this window when appearing
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

		if (ImGui::BeginPopupModal("Project Info", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text(ProjectConfig::ProjectName.c_str());
			ImGui::Text(("Location: " + ProjectConfig::ProjectLocation.string()).c_str());
			ImGui::Text(("Version: " + ProjectConfig::ProjectVersion).c_str());

			if (ImGui::Button("OK", ImVec2(120, 0))) 
			{ 
				ImGui::CloseCurrentPopup(); 
			}

			ImGui::EndPopup();
		}
	}
}