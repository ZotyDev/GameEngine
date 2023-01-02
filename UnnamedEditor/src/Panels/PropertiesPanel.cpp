#include "uepch.h"
#include "Panels/PropertiesPanel.h"

#include "imgui.h"

#include "EditorConfig.h"
#include "Project/Project.h"

namespace UE
{
	PropertiesPanel::PropertiesPanel()
	{}

	void PropertiesPanel::OnImGuiRender()
	{
		if (ActivePanelsConfig::Properties && !(PanelsConfig::MaximizeOnPlay && ProjectConfig::ProjectRunning && !ProjectConfig::ProjectPaused) && Project::Header::IsOpen)
		{
			ImGui::Begin("Properties");
			ImGui::BeginChild("##properties");

			ImGui::Text(CurrentPath.c_str());

			if (CurrentFilenameExtension == "matdef")
			{
				ImGui::Text("Editing a material");

				if (ImGui::Button("Add"))
				{
					ImGui::OpenPopup("MaterialAddPopup");
				}
				if (ImGui::BeginPopup("MaterialAddPopup"))
				{
					if (ImGui::MenuItem("Vertex Input"))
					{

					}

					if (ImGui::MenuItem("Vertex Output"))
					{

					}

					if (ImGui::MenuItem("Vertex Uniform"))
					{

					}

					ImGui::Separator();

					if (ImGui::MenuItem("Fragment Input"))
					{

					}

					if (ImGui::MenuItem("Fragment Output"))
					{

					}

					if (ImGui::MenuItem("Fragment Uniform"))
					{

					}

					ImGui::EndPopup();
				}
			}
			else if (CurrentFilenameExtension == "frag")
			{
				ImGui::Text("Editing a fragment shader");
			}
			else if (CurrentFilenameExtension == "vert")
			{
				ImGui::Text("Editing a vertex shader");
			}

			ImGui::EndChild();

			if (ImGui::BeginDragDropTarget())
			{
				// Receive payload from content browser
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
				{
					const wchar_t* path = (const wchar_t*)payload->Data;
					std::wstring Test(path);

					// Get the file location
					UEString ReceivedPath = UEString(Test.begin(),Test.end());

					// Get the file extension if it's not a directory
					CurrentFilenameExtension.clear();
					if (UEUint32 DotLocation = ReceivedPath.find_last_of("."); DotLocation < ReceivedPath.size())
					{
						// Set the current path
						CurrentPath = ReceivedPath;

						// Set the current filename extension
						CurrentFilenameExtension = ReceivedPath.substr(DotLocation + 1);
					}
				}
				ImGui::EndDragDropTarget();
			}
			ImGui::End();
		}
	}
}