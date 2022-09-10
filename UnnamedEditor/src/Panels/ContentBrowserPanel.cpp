#include "uepch.h"
#include "Panels/ContentBrowserPanel.h"

#include <imgui.h>

#include "Project/Project.h"

#include "Panels/PanelsConfig.h"

namespace UE
{
	std::vector<UEString> IconsToBeLoaded = {
		"Directory",
		"File",
		"Back",
		"png",
		"lua",
		"ttf",
		"txt",
		"wav",
		"vert",
		"frag",
		"matdef",
		"mat",
		"toml"
	};

	ContentBrowserPanel::ContentBrowserPanel()
	{
		for (const auto& it : IconsToBeLoaded)
		{
			Ref<Texture2D> CurrentIconTexture = Texture2D::Create();
			CurrentIconTexture->LoadFromSource("res/Editor/ContentBrowser/" + it + ".png");
			m_Icons.insert({ it, CurrentIconTexture });
		}
	}

	void ContentBrowserPanel::OnImGuiRender()
	{
		if (ActivePanelsConfig::ContentBrowser && !(PanelsConfig::MaximizeOnPlay && PanelsConfig::ProjectRunning) && Project::Header::IsOpen)
		{
			ImGui::Begin("Content Browser");

			if (Project::Header::CurrentDirectory != Project::Header::AssetPath)
			{
				if (ImGui::ImageButton((ImTextureID)m_Icons["Back"]->GetID(), { 15.0f, 15.0f }, { 0, 1 }, { 1, 0 }))
				{
					Project::Header::CurrentDirectory = Project::Header::CurrentDirectory.parent_path();
				}
			}

			static float Padding = 16.0f;
			static float ThumbnailSize = 120.0f;
			float CellSize = Padding + ThumbnailSize;

			float PanelWidth = ImGui::GetContentRegionAvail().x;
			int ColumnCount = (int)(PanelWidth / CellSize);
			if (ColumnCount < 1)
			{
				ColumnCount = 1;
			}

			ImGui::Columns(ColumnCount, 0, false);

			for (auto& directoryEntry : std::filesystem::directory_iterator(Project::Header::CurrentDirectory))
			{
				const UEPath& Path = directoryEntry.path();
				UEPath RelativePath = std::filesystem::relative(Path, Project::Header::AssetPath);
				UEString FilenameString = RelativePath.filename().string();

				ImGui::PushID(FilenameString.c_str());
				Ref<Texture2D> Icon;
				UEString FilenameExtension = FilenameString.substr(FilenameString.find_last_of(".") + 1);
				if (directoryEntry.is_directory())
				{
					Icon = m_Icons["Directory"];
				}
				else if (m_Icons.find(FilenameExtension) != m_Icons.end())
				{
					Icon = m_Icons[FilenameExtension];
				}
				else
				{
					Icon = m_Icons["File"];
				}

				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
				ImGui::ImageButton((ImTextureID)Icon->GetID(), { ThumbnailSize, ThumbnailSize }, { 0, 1 }, { 1, 0 });
				ImGui::PopStyleColor();

				if (ImGui::BeginDragDropSource())
				{
					const wchar_t* ItemPath = RelativePath.c_str();
					ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", ItemPath, (wcslen(ItemPath) + 1) * sizeof(wchar_t));
					ImGui::Text(FilenameString.c_str());
					ImGui::EndDragDropSource();
				}

				if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
				{
					if (directoryEntry.is_directory())
					{
						Project::Header::CurrentDirectory /= Path.filename();
					}
					else if (FilenameExtension == "lua" || FilenameExtension == "toml")
					{
						UEString CommandString = "code ";
						CommandString += (Project::Header::CurrentDirectory / Path.filename()).string();
						// Todo:zoty find a better way of doing this
						system(CommandString.c_str());
					}
				}
				ImGui::TextWrapped(FilenameString.c_str());

				ImGui::NextColumn();

				ImGui::PopID();
			}

			ImGui::Columns(1);

			ImGui::End();
		}
	}
}