#include "uepch.h"
#include "Panels/ContentBrowserPanel.h"

#include <imgui.h>

#include "Project/Project.h"

#include "EditorConfig.h"

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

	static ImGuiTextFilter Filter;

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
		if (ActivePanelsConfig::ContentBrowser && !(PanelsConfig::MaximizeOnPlay && ProjectConfig::ProjectRunning) && Project::Header::IsOpen)
		{
			ImGui::Begin("Content Browser");
			
			if (ImGui::ImageButton((ImTextureID)m_Icons["Back"]->GetID(), { 15.0f, 15.0f }, { 0, 1 }, { 1, 0 } ))
			{
				if (Project::Header::CurrentDirectory != Project::Header::AssetPath)
				{
					Project::Header::CurrentDirectory = Project::Header::CurrentDirectory.parent_path();
				}
			}
			
			ImGui::SameLine();

			Filter.Draw("##searchbar", 340.0f);

			ImGui::SameLine();
		
			if (Project::Header::CurrentDirectory == Project::Header::AssetPath)
			{
				ImGui::Text("Assets");
			}
			else
			{
				auto HeaderLocation = std::filesystem::relative(Project::Header::CurrentDirectory, Project::Header::AssetPath);
				ImGui::Text(("Assets/" + HeaderLocation.string()).c_str());
			}
			
			ImGui::Separator();

			static float Padding = 16.0f;
			static float ThumbnailSize = 128.0f;
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

				if (Filter.PassFilter(FilenameString.c_str()))
				{
					ImGui::PushID(FilenameString.c_str());
					Ref<Texture2D> Icon;
					UEString FilenameExtension = FilenameString.substr(FilenameString.find_last_of(".") + 1);
					if (directoryEntry.is_directory())
					{
						if (std::filesystem::is_empty(directoryEntry))
						{
							Icon = m_Icons["Empty Folder"];
						}
						else
						{
							Icon = m_Icons["Folder"];
						}
					}
					else if (m_Icons.find(FilenameExtension) != m_Icons.end())
					{
						Icon = m_Icons[FilenameExtension];
					}
					else
					{
						Icon = m_Icons["File"];
					}

					ImGui::BeginChild(("#" + FilenameString).c_str(), {-1.0f, -1.0f}, false);

					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
					ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered));
					ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ThumbnailSize) * 0.5f);
					ImGui::ImageButton((ImTextureID)Icon->GetID(), { ThumbnailSize, ThumbnailSize }, { 0, 1 }, { 1, 0 });
					ImGui::PopStyleColor(2);

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
					auto WindowWidth = ImGui::GetWindowSize().x;
					auto TextWidth = ImGui::CalcTextSize(FilenameString.c_str()).x;
					//ImGui::SetCursorPosX((WindowWidth - TextWidth) * 0.5f);
					UEFloat TextPositionHelper = (WindowWidth - TextWidth) * 0.5f;
					if (TextPositionHelper < 0)
					{
						ImGui::PushTextWrapPos(TextPositionHelper);
					}
					else
					{
						ImGui::SetCursorPosX(TextPositionHelper);
					}
					//ImGui::PushTextWrapPos((WindowWidth - TextWidth) * 0.5f);
					ImGui::TextWrapped(FilenameString.c_str());

					ImGui::EndChild();

					ImGui::NextColumn();

					ImGui::PopID();
				}
			}

			ImGui::Columns(1);

			ImGui::End();
		}
	}
}