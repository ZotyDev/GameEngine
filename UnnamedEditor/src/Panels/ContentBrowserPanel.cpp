#include "uepch.h"
#include "Panels/ContentBrowserPanel.h"

#include <imgui.h>

#include "ProjectConfig.h"

#include "Panels/PanelsConfig.h"

namespace UE
{
	ContentBrowserPanel::ContentBrowserPanel()
	{
		m_DirectoryIcon = Texture2D::Create();
		m_DirectoryIcon->LoadFromSource("res/Editor/ContentBrowser/Directory.png");

		m_FileIcon = Texture2D::Create();
		m_FileIcon->LoadFromSource("res/Editor/ContentBrowser/File.png");

		m_ImageIcon = Texture2D::Create();
		m_ImageIcon->LoadFromSource("res/Editor/ContentBrowser/Image.png");
		
		m_LuaScriptIcon = Texture2D::Create();
		m_LuaScriptIcon->LoadFromSource("res/Editor/ContentBrowser/LuaScript.png");

		m_FontIcon = Texture2D::Create();
		m_FontIcon->LoadFromSource("res/Editor/ContentBrowser/Font.png");

		m_TextIcon = Texture2D::Create();
		m_TextIcon->LoadFromSource("res/Editor/ContentBrowser/Text.png");

		m_AudioIcon = Texture2D::Create();
		m_AudioIcon->LoadFromSource("res/Editor/ContentBrowser/Audio.png");

		m_VertexShaderIcon = Texture2D::Create();
		m_VertexShaderIcon->LoadFromSource("res/Editor/ContentBrowser/VertexShader.png");

		m_FragmentShaderIcon = Texture2D::Create();
		m_FragmentShaderIcon->LoadFromSource("res/Editor/ContentBrowser/FragmentShader.png");

		m_MaterialDefinitionIcon = Texture2D::Create();
		m_MaterialDefinitionIcon->LoadFromSource("res/Editor/ContentBrowser/MaterialDefinition.png");

		m_MaterialIcon = Texture2D::Create();
		m_MaterialIcon->LoadFromSource("res/Editor/ContentBrowser/Material.png");
	}

	void ContentBrowserPanel::OnImGuiRender()
	{
		if (PanelsShowConfig::ShowContentBrowser && !(PanelsConfig::MaximizeOnPlay && PanelsConfig::ProjectRunning))
		{

			ImGui::Begin("Content Browser");

			if (ProjectConfig::CurrentDirectory != ProjectConfig::AssetPath)
			{
				if (ImGui::Button("<-"))
				{
					ProjectConfig::CurrentDirectory = ProjectConfig::CurrentDirectory.parent_path();
				}
			}

			static float Padding = 16.0f;
			static float ThumbnailSize = 66.66f;
			float CellSize = Padding + ThumbnailSize;

			float PanelWidth = ImGui::GetContentRegionAvail().x;
			int ColumnCount = (int)(PanelWidth / CellSize);
			if (ColumnCount < 1)
			{
				ColumnCount = 1;
			}

			ImGui::Columns(ColumnCount, 0, false);

			for (auto& directoryEntry : std::filesystem::directory_iterator(ProjectConfig::CurrentDirectory))
			{
				const UEPath& Path = directoryEntry.path();
				UEPath RelativePath = std::filesystem::relative(Path, ProjectConfig::AssetPath);
				UEString FilenameString = RelativePath.filename().string();

				ImGui::PushID(FilenameString.c_str());
				Ref<Texture2D> Icon;
				UEString FilenameExtension = FilenameString.substr(FilenameString.find_last_of(".") + 1);
				if (directoryEntry.is_directory())
				{
					Icon = m_DirectoryIcon;
				}
				else if (FilenameExtension == "png")
				{
					Icon = m_ImageIcon;
				}
				else if (FilenameExtension == "lua")
				{
					Icon = m_LuaScriptIcon;
				}
				else if (FilenameExtension == "ttf")
				{
					Icon = m_FontIcon;
				}
				else if (FilenameExtension == "txt")
				{
					Icon = m_TextIcon;
				}
				else if (FilenameExtension == "wav")
				{
					Icon = m_AudioIcon;
				}
				else if (FilenameExtension == "vert")
				{
					Icon = m_VertexShaderIcon;
				}
				else if (FilenameExtension == "frag")
				{
					Icon = m_FragmentShaderIcon;
				}
				else if (FilenameExtension == "matdef")
				{
					Icon = m_MaterialDefinitionIcon;
				}
				else if (FilenameExtension == "mat")
				{
					Icon = m_MaterialIcon;
				}
				else
				{
					Icon = m_FileIcon;
				}

				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
				ImGui::ImageButton((ImTextureID)Icon->GetID(), { ThumbnailSize, ThumbnailSize }, { 0, 1 }, { 1, 0 });

				if (ImGui::BeginDragDropSource())
				{
					const wchar_t* ItemPath = RelativePath.c_str();
					ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", ItemPath, (wcslen(ItemPath) + 1) * sizeof(wchar_t));
					ImGui::Text(FilenameString.c_str());
					ImGui::EndDragDropSource();
				}

				ImGui::PopStyleColor();
				if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
				{
					if (directoryEntry.is_directory())
					{
						ProjectConfig::CurrentDirectory /= Path.filename();
					}
				}
				ImGui::TextWrapped(FilenameString.c_str());

				ImGui::NextColumn();

				ImGui::PopID();
			}

			ImGui::Columns(1);

			ImGui::SliderFloat("Thumbnail Size", &ThumbnailSize, 16, 512);
			ImGui::SliderFloat("Padding", &Padding, 0, 32);

			// TODO: status bar
			ImGui::End();

		}
	}
}