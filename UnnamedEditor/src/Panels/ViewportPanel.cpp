#include "uepch.h"
#include "Panels/ViewportPanel.h"

#include <imgui.h>

#include "EditorConfig.h"
#include "Core/GlobalConfig.h"

#include "Project/Project.h"

#include "Renderer/Texture.h"

namespace UE
{
	Ref<Texture2D> m_ContinueIcon;
	Ref<Texture2D> m_PauseIcon;
	Ref<Texture2D> m_PlayIcon;
	Ref<Texture2D> m_StopIcon;

	ViewportPanel::ViewportPanel()
	{
		m_ContinueIcon = Texture2D::Create();
		m_PauseIcon = Texture2D::Create();
		m_PlayIcon = Texture2D::Create();
		m_StopIcon = Texture2D::Create();

		m_ContinueIcon->LoadFromSource("res/Editor/Viewport/Continue.png");
		m_PauseIcon->LoadFromSource("res/Editor/Viewport/Pause.png");
		m_PlayIcon->LoadFromSource("res/Editor/Viewport/Play.png");
		m_StopIcon->LoadFromSource("res/Editor/Viewport/Stop.png");
	}

	void ViewportPanel::OnImGuiRender(Ref<Application::SharedData> data, glm::vec2* viewportBounds, glm::vec2* viewportSize, Ref<Framebuffer> framebuffer)
	{
		if (ActivePanelsConfig::Viewport && Project::Header::IsOpen)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
			ImGui::Begin("Viewport");
			auto ViewportMinRegion = ImGui::GetWindowContentRegionMin();
			auto ViewportMaxRegion = ImGui::GetWindowContentRegionMax();
			auto ViewportOffset = ImGui::GetWindowPos();
			viewportBounds[0] = { ViewportMinRegion.x + ViewportOffset.x, ViewportMinRegion.y + ViewportOffset.y };
			viewportBounds[1] = { ViewportMaxRegion.x + ViewportOffset.x, ViewportMaxRegion.y + ViewportOffset.y };

			PanelsConfig::ViewportFocused = ImGui::IsWindowFocused();
			PanelsConfig::ViewportHovered = ImGui::IsWindowHovered();
			data->m_ImGuiLayer->BlockEvents(!PanelsConfig::ViewportFocused && !PanelsConfig::ViewportHovered);

			ImVec2 ViewportPanelSize = ImGui::GetContentRegionAvail();
			*viewportSize = { ViewportPanelSize.x, ViewportPanelSize.y };

			GlobalConfig::Renderer::ScreenWidth = (UEUint32)ViewportPanelSize.x;
			GlobalConfig::Renderer::ScreenHeight = (UEUint32)ViewportPanelSize.y;

			// Todo:zoty the framebuffer should be rendered, and only after that used here
			UEUint64 TextureID = framebuffer->GetColorAttachmentRendererID();
		
			ImGui::Image(reinterpret_cast<void*>(TextureID), ImVec2{ viewportSize->x, viewportSize->y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 0.0f, 0.0f });
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 5.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });
			ImGui::PushStyleColor(ImGuiCol_Button, {});
			auto BackgroundColor = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg);
			BackgroundColor.w *= 0.5f;
			ImGui::PushStyleColor(ImGuiCol_ChildBg, BackgroundColor);
			ImGui::SetNextWindowPos({ viewportBounds[0][0] + GlobalConfig::Renderer::ScreenWidth * 0.5f - 32.0f, viewportBounds[0][1] + 5.0f });
			ImGui::BeginChild("test", {32 * 2, 32});

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 0.0f, 0.0f });
			if (ProjectConfig::ProjectRunning)
			{
				if (ProjectConfig::ProjectPaused)
				{
					if (ImGui::ImageButton((ImTextureID)m_ContinueIcon->GetID(), { 32.0f, 32.0f }))
					{
						ProjectConfig::ProjectPaused = false;
					}
				}
				else
				{
					if (ImGui::ImageButton((ImTextureID)m_PauseIcon->GetID(), { 32.0f, 32.0f }))
					{
						ProjectConfig::ProjectPaused = true;
					}
				}
			}
			else
			{
				if (ImGui::ImageButton((ImTextureID)m_PlayIcon->GetID(), { 32.0f, 32.0f }))
				{
					ProjectConfig::ProjectRunning = true;
				}
			}
			
			ImGui::SameLine();
			if (ProjectConfig::ProjectRunning)
			{
				if (ImGui::ImageButton((ImTextureID)m_StopIcon->GetID(), { 32.0f, 32.0f }))
				{
					ProjectConfig::ProjectRunning = false;
					ProjectConfig::ProjectPaused = false;
				}
			}
			else
			{
				ImGui::ImageButton((ImTextureID)m_StopIcon->GetID(), { 32.0f, 32.0f }, {}, { 1, 1 }, -1, {}, { 0.1f, 0.1f, 0.1f, 0.4f });
			}
			
			ImGui::PopStyleVar();

			ImGui::EndChild();
			ImGui::PopStyleVar(5);
			ImGui::PopStyleColor(2);

			ImGui::End();
			ImGui::PopStyleVar();
		}
	}
}