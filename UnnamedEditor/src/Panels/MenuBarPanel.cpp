#include "uepch.h"
#include "Panels/MenuBarPanel.h"

#include <imgui.h>

#include "EditorConfig.h"

#include "Project/Project.h"
#include "Project/ProjectSerializer.h"

namespace UE
{
	MenuBarPanel::MenuBarPanel()
	{}

	UEBool NewProjectPopupTemp = false;
	UEBool OpenProjectPopupTemp = false;
	UEBool ProjectInfoPopupTemp = false;
	
	UEBool FolderAlreadyExistsError = false;
	UEBool NameEmptyError = false;
	UEBool VersionEmptyError = false;
	UEBool LocationEmptyError = false;
	UEBool InvalidProjectError = false;

	char ProjectNameBuffer[256] = "";
	char ProjectVersionBuffer[256] = "";
	char ProjectLocationBuffer[256] = "";

	void MenuBarPanel::OnImGuiRender(Ref<Application::SharedData> data)
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Project"))
			{
				if (ImGui::MenuItem("New", "Ctrl+N"))
				{
					NewProjectPopupTemp = true;
				}

				if (ImGui::MenuItem("Open..", "Ctrl+O"))
				{
					OpenProjectPopupTemp = true;
				}

				if (ImGui::BeginMenu("Open Recent", ProjectConfig::RecentProjects.size() != 0))
				{
					auto RecentProjectsView = ProjectConfig::RecentProjects;
					for (auto& it = RecentProjectsView.rbegin(); it != RecentProjectsView.rend(); ++it)
					{
						if (ImGui::MenuItem(it->c_str()))
						{
							ProjectSerializer::Deserialize(*it);
						}
					}
					ImGui::EndMenu();
				}

				if (ImGui::MenuItem("Save", "Ctrl+S", false, Project::Header::IsOpen))
				{
					ProjectSerializer::Serialize(Project::Header::Location);
				}

				if (ImGui::MenuItem("Save As..", "Ctrl+Shift+S", false, Project::Header::IsOpen))
				{

				}

				ImGui::Separator();

				if (ImGui::MenuItem("Project Info", NULL, false, Project::Header::IsOpen))
				{
					ProjectInfoPopupTemp = true;
				}

				ImGui::Separator();

				if (ImGui::BeginMenu("Options", Project::Header::IsOpen))
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

			if (ImGui::BeginMenu("View", Project::Header::IsOpen))
			{
				if (ImGui::MenuItem("Viewport", NULL, &ActivePanelsConfig::Viewport))
				{

				}

				if (ImGui::MenuItem("Content Browser", NULL, &ActivePanelsConfig::ContentBrowser))
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

				if (ImGui::MenuItem("Node Editor", NULL, &ActivePanelsConfig::NodeEditor))
				{

				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Game", Project::Header::IsOpen))
			{
				if (ImGui::MenuItem("Play", !ProjectConfig::ProjectRunning ? "F9" : NULL, nullptr, !ProjectConfig::ProjectRunning))
				{
					if (PanelsConfig::MaximizeOnPlay)
					{
					}

					ProjectConfig::ProjectRunning = true;
				}

				if (ImGui::MenuItem("Stop", ProjectConfig::ProjectRunning? "F9" : NULL, nullptr, ProjectConfig::ProjectRunning))
				{
					ProjectConfig::ProjectRunning = false;
					ProjectConfig::ProjectPaused = false;
				}

				if (ImGui::MenuItem("Pause", NULL, nullptr, !ProjectConfig::ProjectPaused && ProjectConfig::ProjectRunning))
				{
					ProjectConfig::ProjectPaused = true;
				}

				if (ImGui::MenuItem("Resume", NULL, nullptr, ProjectConfig::ProjectPaused))
				{
					ProjectConfig::ProjectPaused = false;
				}

				ImGui::Separator();

				if (ImGui::MenuItem("Hot Reload", "F5", nullptr, ProjectConfig::ProjectRunning))
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
			ImGui::PushItemWidth(350.0f);
			ImGui::InputText("##ProjectName", ProjectNameBuffer, 256);
			ImGui::PopItemWidth();
			if (NameEmptyError)
			{
				ImGui::TextColored({ 1.0f, 0.0f, 0.0f, 1.0f }, "Name cannot be empty");
			}

			ImGui::Text("Project Version:");
			ImGui::PushItemWidth(350.0f);
			ImGui::InputText("##ProjectVersion", ProjectVersionBuffer, 256);
			ImGui::PopItemWidth();
			if (VersionEmptyError)
			{
				ImGui::TextColored({ 1.0f, 0.0f, 0.0f, 1.0f }, "Version cannot be empty");
			}

			ImGui::Text("Project Location:");
			
			ImGui::InputText("##ProjectLocation", ProjectLocationBuffer, 256);
			ImGui::SameLine();
			if (ImGui::Button("Browse"))
			{
				UEPath TempPathHolder;
				if (FileSystem::FileSelectorDialog(TempPathHolder, {}, true))
				{
					std::strcpy(ProjectLocationBuffer, TempPathHolder.string().c_str());
				}
			}
			if (FolderAlreadyExistsError)
			{
				ImGui::TextColored({ 1.0f, 0.0f, 0.0f, 1.0f }, "There is already a project with this name here");
			}
			if (LocationEmptyError)
			{
				ImGui::TextColored({ 1.0f, 0.0f, 0.0f, 1.0f }, "Location cannot be empty");
			}

			ImVec2 ButtonsSize = { (ImGui::GetContentRegionAvail().x - 8) / 2, 0.0f };
			if (ImGui::Button("Create", ButtonsSize))
			{
				Project::Header NewProjectHeader;
				NewProjectHeader.Name = ProjectNameBuffer;
				NewProjectHeader.Version = ProjectVersionBuffer;
				NewProjectHeader.Location = ProjectLocationBuffer;

				UEBool ShouldClose = false;

				ShouldClose |= NameEmptyError = strlen(ProjectNameBuffer) == 0;
				ShouldClose |= VersionEmptyError = strlen(ProjectVersionBuffer) == 0;
				ShouldClose |= LocationEmptyError = strlen(ProjectLocationBuffer) == 0;

				if (!ShouldClose)
				{
					UEString ConfigFilename = UEString(ProjectLocationBuffer) + "/" + ProjectLocationBuffer;
					ShouldClose |= FolderAlreadyExistsError = !Project::Create(NewProjectHeader);
					ProjectSerializer::Serialize(ConfigFilename);
				}

				if (!ShouldClose)
				{
					ImGui::CloseCurrentPopup();

					ProjectNameBuffer[0] = '\0';
					ProjectVersionBuffer[0] = '\0';
					ProjectLocationBuffer[0] = '\0';
				}
			}
			
			ImGui::SetItemDefaultFocus();
			ImGui::SameLine();
			
			if (ImGui::Button("Cancel", ButtonsSize))
			{ 
				ImGui::CloseCurrentPopup(); 

				ProjectNameBuffer[0] = '\0';
				ProjectVersionBuffer[0] = '\0';
				ProjectLocationBuffer[0] = '\0';

				NameEmptyError = false;
				VersionEmptyError = false;
				LocationEmptyError = false;
			}

			ImGui::EndPopup();
		}

		// Always center this window when appearing
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
		if (ImGui::BeginPopupModal("Open Project", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{

			ImGui::Text("Project Location:");
			ImGui::InputText("##ProjectLocation", ProjectLocationBuffer, 256);
			ImGui::SameLine();
			if (ImGui::Button("Browse"))
			{
				UEPath TempPathHolder;
				if (FileSystem::FileSelectorDialog(TempPathHolder, {}, true))
				{
					std::strcpy(ProjectLocationBuffer, TempPathHolder.string().c_str());
				}
			}
			if (LocationEmptyError)
			{
				ImGui::TextColored({ 1.0f, 0.0f, 0.0f, 1.0f }, "Location cannot be empty");
			}
			if (InvalidProjectError)
			{
				ImGui::TextColored({ 1.0f, 0.0f, 0.0f, 1.0f }, "Invalid project location");
			}

			ImVec2 ButtonsSize = { (ImGui::GetContentRegionAvail().x - 8) / 2, 0.0f };
			if (ImGui::Button("Open", ButtonsSize))
			{
				UEBool ShouldClose = false;

				ShouldClose |= LocationEmptyError = strlen(ProjectLocationBuffer) == 0;

				if (!ShouldClose)
				{
					ShouldClose |= InvalidProjectError = !ProjectSerializer::Deserialize(ProjectLocationBuffer);
				}

				if (!ShouldClose)
				{
					ImGui::CloseCurrentPopup();

					ProjectLocationBuffer[0] = '\0';

					LocationEmptyError = false;
					InvalidProjectError = false;
				}
			}

			ImGui::SetItemDefaultFocus();
			ImGui::SameLine();

			if (ImGui::Button("Cancel", ButtonsSize))
			{
				ImGui::CloseCurrentPopup();

				ProjectLocationBuffer[0] = '\0';

				LocationEmptyError = false;
				InvalidProjectError = false;
			}

			ImGui::EndPopup();
		}

		// Always center this window when appearing
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
		if (ImGui::BeginPopupModal("Project Info", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text(Project::Header::Name.c_str());
			ImGui::Text(("Location: " + Project::Header::Location.string()).c_str());
			ImGui::Text(("Version: " + Project::Header::Version).c_str());

			if (ImGui::Button("OK", ImVec2(120, 0))) 
			{ 
				ImGui::CloseCurrentPopup(); 
			}

			ImGui::EndPopup();
		}
	}
}