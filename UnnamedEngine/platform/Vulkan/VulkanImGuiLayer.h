#pragma once

#include "ImGui/ImGuiLayer.h"

namespace UE
{
	class VulkanImGuiLayer : public ImGuiLayer
	{
	public:
		VulkanImGuiLayer() : ImGuiLayer() {}
		~VulkanImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnWindowEvent(Event& event) override;
		virtual void OnInputEvent(Event& event) override;

		virtual void Begin() override;
		virtual void End() override;
	};
}