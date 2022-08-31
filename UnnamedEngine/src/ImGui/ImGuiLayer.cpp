#include "uepch.h"
#include "ImGui/ImGuiLayer.h"

#include <imgui.h>

#if defined(UE_PLATFORM_OPENGL)
	#include <backends/imgui_impl_glfw.h>
	#include "OpenGL/OpenGLImGuiLayer.h"
#endif

#if defined(UE_PLATFORM_VULKAN)
	#include <backends/imgui_impl_glfw.h>
	#include <backends/imgui_impl_vulkan.h>

	#define GLFW_INCLUDE_NONE
	#define GLFW_INCLUDE_VULKAN
	#include <GLFW/glfw3.h>
	#include <vulkan/vulkan.h>
#endif

#include "Renderer/Renderer.h";

namespace UE
{
	Ref<ImGuiLayer> ImGuiLayer::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
			return nullptr;

		#if defined(UE_PLATFORM_OPENGL)
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLImGuiLayer>();
		#endif
		#if defined(UE_PLATFORM_VULKAN)
			return CreateScope<VulkanImGuiLayer>();
		#endif
		}

		UE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{}

	void ImGuiLayer::SetDarkThemeColors()
	{
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Drag and Drop
		colors[ImGuiCol_DragDropTarget] = ImVec4{ 1.0f, 1.0f, 1.0f, 1.0f };
	}
}