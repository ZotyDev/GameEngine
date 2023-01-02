#include "ServerLayer.h"

#include <ImGui/imgui.h>

#include "Debug/Instrumentator.h"

namespace UE
{
	ServerLayer::ServerLayer(Ref<Application::SharedData> data)
		: Layer("ServerLayer"), m_Data(data)
	{}

	void ServerLayer::OnAttach()
	{
		m_Data->m_Window->SetIcon("res/icon.png");

		m_Camera = CreateRef<Camera2D>(
			GlobalConfig::Renderer::ScreenWidth,
			GlobalConfig::Renderer::ScreenHeight,
			glm::vec3(0.0f, 0.0f, 0.0f));
		m_CameraController = CreateRef<CameraController>(m_Camera);

		FramebufferSpecification specs;
		specs.Width = GlobalConfig::Renderer::DesiredWidth;
		specs.Height = GlobalConfig::Renderer::DesiredHeight;
		specs.Samples = 4;
		specs.Attachments = { FramebufferTextureFormat::Color, FramebufferTextureFormat::Depth };
		Ref<Framebuffer> tFramebuffer = Framebuffer::Create(specs);

		specs.Width = GlobalConfig::Renderer::DesiredWidth;
		specs.Height = GlobalConfig::Renderer::DesiredHeight;
		specs.Samples = 1;
		specs.Attachments = { FramebufferTextureFormat::Color };
		Ref<Framebuffer> yFramebuffer = Framebuffer::Create(specs);

		m_Quad = CreateRef<Primitives::Quad>(glm::vec2(-0.5f, 0.5f), glm::vec2(0.5f, -0.5f));

		// LoadShader LUA function register
		LuneFunction LoadShader("LoadShader", [](lua_State* L) -> int
			{
				ShaderLibrary* t_ShaderLibrary = (ShaderLibrary*)lua_touserdata(L, lua_upvalueindex(1));

				const char* t_FilePath = (const char*)lua_tostring(L, -1);

				ShaderLibrary::Load(t_FilePath);
				UE_INFO("Loaded shader: {0}", t_FilePath);

				return 1;
			});

		LoadShader.RegisterSelf(m_Data->m_Lune);
		// Execute file that load the shaders
		m_Data->m_Lune->ExecuteFile("assets/mods/shaders.lua");

		ShaderLibrary::Get("screen")->Compile();
		m_Screen = CreateRef<UE::Screen>(ShaderLibrary::Get("screen"), tFramebuffer, yFramebuffer);

		Renderer2D::Init(m_Screen);
	}

	void ServerLayer::OnDetach()
	{

	}

	void ServerLayer::OnUpdate(Timestep timestep)
	{
		{
			UE_PROFILE_SCOPE("Rendering");
			Renderer::BeginRender(m_CameraController->GetCamera());
			Render();
			Renderer::EndRender();
		}
	}

	void ServerLayer::Render()
	{

	}

	static UEBool Fullscreen = true;
	static UEBool Padding = false;

	void ServerLayer::OnImGuiRender()
	{
		UE_PROFILE_SCOPE("ImGui Rendering");
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (Fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!Padding)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		}

		ImGui::Begin("DockSpace Demo", &m_Data->m_Running, window_flags);
		if (!Padding)
		{
			ImGui::PopStyleVar();
		}

		if (Fullscreen)
		{
			ImGui::PopStyleVar(2);
		}

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::End();
	}

	void ServerLayer::OnWindowEvent(Event& event)
	{

	}

	void ServerLayer::OnInputEvent(Event& event)
	{

	}
}