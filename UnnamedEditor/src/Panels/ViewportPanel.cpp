#include "uepch.h"
#include "Panels/ViewportPanel.h"

#include <imgui.h>

#include "Panels/PanelsConfig.h"

namespace UE
{
	ViewportPanel::ViewportPanel()
	{}

	void ViewportPanel::OnImGuiRender(Ref<Application::SharedData> data, glm::vec2* viewportBounds, glm::vec2* viewportSize, Ref<Framebuffer> framebuffer)
	{
		if (PanelsShowConfig::ShowViewport)
		{
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

			GlobalConfig::Rendering::ScreenWidth = (UEUint32)ViewportPanelSize.x;
			GlobalConfig::Rendering::ScreenHeight = (UEUint32)ViewportPanelSize.y;

			UEUint64 TextureID = framebuffer->GetColorAttachmentRendererID();
			ImGui::Image(reinterpret_cast<void*>(TextureID), ImVec2{ viewportSize->x, viewportSize->y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

			ImGui::End();

		}
	}
}