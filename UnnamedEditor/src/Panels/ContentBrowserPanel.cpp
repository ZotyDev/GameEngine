#include "uepch.h"
#include "Panels/ContentBrowserPanel.h"

#include <imgui.h>
#include <imgui_internal.h>

#include "Project/Project.h"

#include "EditorConfig.h"

namespace UE
{
	std::vector<UEPath> ForwardStack;

	std::vector<UEString> IconsToBeLoaded = {
		"Directory",
		"File",
		"Back",
		"Forward",
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

	ImGuiTextFilter Filter;

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

			if (Project::Header::CurrentDirectory != Project::Header::AssetPath)
			{
				if (ImGui::ImageButton((ImTextureID)m_Icons["Back"]->GetID(), { 15.0f, 15.0f }, { 0, 1 }, { 1, 0 }))
				{
					ForwardStack.push_back(Project::Header::CurrentDirectory);
					Project::Header::CurrentDirectory = Project::Header::CurrentDirectory.parent_path();
				}
			}
			else
			{
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyleColorVec4(ImGuiCol_Button));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyleColorVec4(ImGuiCol_Button));
				ImGui::ImageButton((ImTextureID)m_Icons["Back"]->GetID(), { 15.0f, 15.0f }, { 0, 1 }, { 1, 0 }, -1, ImVec4(0,0,0,0), ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
				ImGui::PopStyleColor(2);
			}
			ImGui::SameLine();
			if (!ForwardStack.empty())
			{
				if (ImGui::ImageButton((ImTextureID)m_Icons["Forward"]->GetID(), { 15.0f, 15.0f }, { 0, 1 }, { 1, 0 }))
				{
					Project::Header::CurrentDirectory = ForwardStack.back();
					ForwardStack.pop_back();
				}
			}
			else
			{
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyleColorVec4(ImGuiCol_Button));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyleColorVec4(ImGuiCol_Button));
				ImGui::ImageButton((ImTextureID)m_Icons["Forward"]->GetID(), { 15.0f, 15.0f }, { 0, 1 }, { 1, 0 }, -1, ImVec4(0, 0, 0, 0), ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
				ImGui::PopStyleColor(2);
			}

			ImGui::SameLine();
			Filter.Draw("###searchbar", 250.0f);

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

				UEBool IsPreview = false;

				if (Filter.PassFilter(FilenameString.c_str()))
				{
					ImGui::PushID(FilenameString.c_str());
					Ref<Texture2D> Icon;
					UEString FilenameExtension = FilenameString.substr(FilenameString.find_last_of(".") + 1);
					if (directoryEntry.is_directory())
					{
						if (std::filesystem::is_empty(directoryEntry))
						{
							Icon = m_Icons["Directory"];
						}
						else
						{
							Icon = m_Icons["Directory"];
						}
					}
					else if (m_Previews.find(Project::Header::AssetPath.string() + "/" + RelativePath.string()) != m_Previews.end())
					{
						Icon = m_Previews[Project::Header::AssetPath.string() + "/" + RelativePath.string()];
						IsPreview = true;
					}
					else if (FilenameExtension == "png" || FilenameExtension == "jpg" || FilenameExtension == "jpeg")
					{
						// Load the image as a preview
						Ref<Texture2D> CurrentPreview = Texture2D::Create();
						UEString PreviewLocation = Project::Header::AssetPath.string() + "/" + RelativePath.string();
						CurrentPreview->LoadFromSourceScaledMax(PreviewLocation, ThumbnailSize);
						m_Previews.insert({ PreviewLocation, CurrentPreview });
						Icon = CurrentPreview;
						IsPreview = true;
					}
					else if (m_Icons.find(FilenameExtension) != m_Icons.end())
					{
						Icon = m_Icons[FilenameExtension];
					}
					else
					{
						Icon = m_Icons["File"];
					}

					ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
					ImGui::BeginChild(("#" + FilenameString).c_str(), { ThumbnailSize, ThumbnailSize * 1.5f }, false);

					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
					ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered));

					ImGuiStyle& Style = ImGui::GetStyle();
					UEFloat Off = (ImGui::GetContentRegionAvail().x - (ThumbnailSize)) * 0.5f;
					if (Off > 0.0f)
					{
						ImGui::SetCursorPosX(ImGui::GetCursorPosX() + Off);
					}
		
					if (IsPreview)
					{
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.0f, 0.0f, 0.0f, 0.0f });
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.0f, 0.0f, 0.0f, 0.0f });
						ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 0.0f, 0.0f });
						
						UEFloat IconSizeX = IconSizeX = (UEFloat)Icon->GetWidth();
						UEFloat IconSizeY = IconSizeY = (UEFloat)Icon->GetHeight();
						
						if (Icon->GetWidth() < ThumbnailSize && Icon->GetHeight() < ThumbnailSize)
						{
							UEFloat IconRatio = Icon->GetRatio();
							IconSizeX = IconSizeX * IconRatio;
							IconSizeY = IconSizeY * IconRatio;
						}

						if (Icon->GetWidth() < Icon->GetHeight())
						{
							UEFloat Off = (ImGui::GetContentRegionAvail().x - Icon->GetWidth()) * 0.25f;
							if (Off > 0.0f)
							{
								ImGui::SetCursorPosX(ImGui::GetCursorPosX() + Off);
							}
						}

						ImGui::ImageButton((ImTextureID)Icon->GetID(), { IconSizeX , IconSizeY }, {0, 1}, {1, 0});
						ImGui::PopStyleVar();
						ImGui::PopStyleColor(4);
					}
					else
					{
						ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 0.0f, 0.0f });
						ImGui::ImageButton((ImTextureID)Icon->GetID(), { ThumbnailSize, ThumbnailSize }, { 0, 1 }, { 1, 0 });
						ImGui::PopStyleVar();
						ImGui::PopStyleColor(2);
					}

					if (ImGui::BeginDragDropSource())
					{
						const wchar_t* ItemPath = RelativePath.c_str();
						ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", ItemPath, (wcslen(ItemPath) + 1) * sizeof(wchar_t));					
						ImGui::Text(FilenameString.c_str());
						ImGui::EndDragDropSource();
					}

					if (ImGui::IsItemHovered())
					{
						if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
						{
							if (directoryEntry.is_directory())
							{
								Project::Header::CurrentDirectory /= Path.filename();
								ForwardStack.clear();
							}
							else if (FilenameExtension == "lua" || FilenameExtension == "yaml")
							{
								UEString CommandString = "code ";
								CommandString += (Project::Header::CurrentDirectory / Path.filename()).string();
								// Todo:zoty find a better way of doing this
								system(CommandString.c_str());
							}
						}
					}

					// Big text handler
					UEFloat WindowWidth = ImGui::GetWindowSize().x;
					UEFloat TextWidth = ImGui::CalcTextSize(FilenameString.c_str()).x;
					UEInt32 TextSize = FilenameString.length();
					//UE_CORE_INFO("{} -\n {}", FilenameString, TextSize);
					UEInt32 TextMaxSize = 47;
					UEInt32 TextSizeDiff = TextSize - TextMaxSize;
					UEFloat TextPositionHelper = (WindowWidth - TextWidth) * 0.5f;
					if (TextSizeDiff > 0)
					{
						FilenameString.erase(FilenameString.begin() + TextMaxSize, FilenameString.end());
						FilenameString.replace(TextMaxSize - 3, TextMaxSize, "...");
					}
					if (TextPositionHelper < 0)
					{
						ImGui::PushTextWrapPos(TextPositionHelper);
					}
					else
					{
						ImGui::SetCursorPosX(TextPositionHelper);
					}
					ImGui::TextWrapped(FilenameString.c_str());

					ImGui::EndChild();
					ImGui::PopStyleVar();

					ImGui::NextColumn();

					ImGui::PopID();
				}
			}

			ImGui::Columns(1);

			ImGui::End();
		}
	}
}