#include "uepch.h"
#include "OpenGL/OpenGLImGuiLayer.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <implot.h>

#include <imgui_node_editor.h>

#include "Core/Application.h"

namespace UE
{
	void OpenGLImGuiLayer::OnAttach()
	{
		// Setúp dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImPlot::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		float FontSize = 18.0f;
		io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Bold.ttf", FontSize);
		io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Regular.ttf", FontSize);

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical do regular ones
		ImGuiStyle& Style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			Style.WindowRounding = 0.0f;
			Style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		SetDarkThemeColors();

		Application& App = Application::Get();
		GLFWwindow* Window = static_cast<GLFWwindow*>(App.GetWindow().GetNativeWindow());

		// Setup platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(Window, true);
		ImGui_ImplOpenGL3_Init("#version 460");
	}

	void OpenGLImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		//ImGui_ImplGlfw_Shutdown(); // useless since main app glfw gets destroyed before, it just throw errors
		ImPlot::DestroyContext();
		ImGui::DestroyContext();
	}

	void OpenGLImGuiLayer::OnWindowEvent(Event& event)
	{
	}

	void OpenGLImGuiLayer::OnInputEvent(Event& event)
	{
		if (m_BlockingEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
			event.m_Handled |= event.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
			event.m_Handled |= event.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
		}
	}

	void OpenGLImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		//ImGuizmo::BeginFrame();
	}

	void OpenGLImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& App = Application::Get();
		io.DisplaySize = ImVec2((float)App.GetWindow().GetWidth(), (float)App.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
}