#include "EditorLayer.h"

#include <imgui.h>
#include <imgui_internal.h>

#include <Panels/PanelsConfig.h>

namespace UE
{
	EditorLayer::EditorLayer(Ref<Application::SharedData> data)
		: Layer("EditorLayer"), m_Data(data)
	{}

	Ref<Material> GrassMaterial = CreateRef<Material>();

	void EditorLayer::OnAttach()
	{
		// Set the icon for the game window
		m_Data->m_Window->SetIcon("res/icon.png");

		m_Data->m_Lune->ExecuteFile("assets/mods/test.lua");

		m_Texture2D = Texture2D::Create();
		const UEString TexturePath = "assets/textures/grass.png";
		if (m_Texture2D->LoadFromSource(TexturePath) == UEResult::Error)
		{
			UE_CORE_ERROR("Failed to load {0}: not found", TexturePath);
		}

		m_Camera = CreateRef<Camera3D>(1280, 720, glm::vec3(0.0f, 0.0f, 1.5f));
		m_CameraController = CreateRef<CameraController>(m_Camera);

		FramebufferSpecification specs;
		specs.Width = 1280;
		specs.Height = 720;
		specs.Attachments.Attachments.push_back(FramebufferTextureSpecification(FramebufferTextureFormat::Color));
		specs.Attachments.Attachments.push_back(FramebufferTextureSpecification(FramebufferTextureFormat::Depth));
		m_Framebuffer = Framebuffer::Create(specs);

		m_Quad = CreateRef<Primitives::Quad>(glm::vec2(-0.5f, 0.5f), glm::vec2(0.5f, -0.5f));

		// LoadShader LUA function register
		LuneFunction LoadShader("LoadShader", [](lua_State* L) -> int
			{
				UE::ShaderLibrary* t_ShaderLibrary = (ShaderLibrary*)lua_touserdata(L, lua_upvalueindex(1));

				const char* t_FilePath = (const char*)lua_tostring(L, -1);

				t_ShaderLibrary->Load(t_FilePath);
				UE_INFO("Loaded shader: {0}", t_FilePath);

				return 1;
			}, (void*)m_ShaderLibrary.get());

		LoadShader.RegisterSelf(m_Data->m_Lune);
		// Execute file that load the shaders
		m_Data->m_Lune->ExecuteFile("assets/mods/shaders.lua");

		m_ShaderLibrary->Get("screen")->Compile();
		//m_ShaderLibrary->Get("default")->Compile();

		m_Screen = CreateRef<UE::Screen>(m_ShaderLibrary->Get("screen"), m_Framebuffer);

		Renderer3D::Init(m_Screen);

		ShaderHeaderConstructor MyShaderHeaderConstructor("assets/shaders/default");

		MyShaderHeaderConstructor.AddElement({
			"v_Position",
			ShaderDataType::Vec3,
			ShaderHeaderConstructor::UseType::VertInput,
			});

		MyShaderHeaderConstructor.AddElement({
			"v_Texture",
			ShaderDataType::Vec2,
			ShaderHeaderConstructor::UseType::VertInput,
			});

		MyShaderHeaderConstructor.AddElement({
			"Texture",
			ShaderDataType::Vec2,
			ShaderHeaderConstructor::UseType::VertOutput,
			});
		MyShaderHeaderConstructor.AddElement({
			"FragColor",
			ShaderDataType::Vec4,
			ShaderHeaderConstructor::UseType::FragOutput,
			});
		MyShaderHeaderConstructor.AddElement({
			"u_Transform",
			ShaderDataType::Mat4,
			ShaderHeaderConstructor::UseType::VertUniform,
			});

		UEString NewVertSource;
		UEString NewFragSource;
		MyShaderHeaderConstructor.Construct(NewVertSource, NewFragSource);

		m_ShaderLibrary->Get("default")->Set(NewVertSource, NewFragSource);
	}

	void EditorLayer::OnDetach()
	{
		
	}

	void EditorLayer::OnUpdate(Timestep timestep)
	{
		m_CameraController->OnUpdate(timestep);

		Render();
	}

	void EditorLayer::Render()
	{
		if 
			(
				FramebufferSpecification spec = m_Framebuffer->GetSpecification();
				m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
				(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y)
			)
		{
			m_CameraController->OnResize(m_ViewportSize.x, m_ViewportSize.y);
			Renderer::OnWindowResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}

		Renderer3D::BeginRender(m_CameraController->GetCamera());
		/*============================================================================*/

		//Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, 0.0f, 0.0f });
		//Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 1.0f, 0.0f, 0.0f });
		//Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, 1.0f, 0.0f });
		//Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, 0.0f, 1.0f });
		//Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { -1.0f, 0.0f, 0.0f });
		//Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, -1.0f, 0.0f });
		//Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, 0.0f, -1.0f });

		/*============================================================================*/
		Renderer3D::EndRender();
	}

	void EditorLayer::OnImGuiRender()
	{
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (PanelsConfig::OptFullscreen)
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
		if (!PanelsConfig::OptPadding)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		}

		ImGui::Begin("DockSpace Demo", &m_Data->m_Running, window_flags);
		if (!PanelsConfig::OptPadding)
		{
			ImGui::PopStyleVar();
		}

		if (PanelsConfig::OptFullscreen)
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

		m_MenuBarPanel.OnImGuiRender(m_Data);
		m_ViewportPanel.OnImGuiRender(m_Data, m_ViewportBounds, &m_ViewportSize, m_Framebuffer);
		m_ContentBrowserPanel.OnImGuiRender();
		m_SceneHierarchyPanel.OnImGuiRender();
		m_PropertiesPanel.OnImGuiRender();

		ImGui::End();

		//ImGui::ShowDemoWindow();
	}

	void EditorLayer::OnWindowEvent(Event& event)
	{
		m_CameraController->OnEvent(event);

		UE::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowResizeEvent>(UE_BIND_EVENT_FN(OnWindowResize));
	}

	void EditorLayer::OnInputEvent(Event& event)
	{
		UE::EventDispatcher dispatcher(event);

		dispatcher.Dispatch<KeyPressedEvent>(UE_BIND_EVENT_FN(OnKeyPressed));
		dispatcher.Dispatch<KeyReleasedEvent>(UE_BIND_EVENT_FN(OnKeyReleased));
		dispatcher.Dispatch<KeyTypedEvent>(UE_BIND_EVENT_FN(OnKeyTyped));
		dispatcher.Dispatch<MouseButtonPressedEvent>(UE_BIND_EVENT_FN(OnMousePressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(UE_BIND_EVENT_FN(OnMouseReleased));
		dispatcher.Dispatch<MouseMovedEvent>(UE_BIND_EVENT_FN(OnMouseMoved));
		dispatcher.Dispatch<MouseScrolledEvent>(UE_BIND_EVENT_FN(OnMouseScrolled));
		dispatcher.Dispatch<GamepadButtonPressedEvent>(UE_BIND_EVENT_FN(OnGamepadButtonPressed));
		dispatcher.Dispatch<GamepadButtonReleasedEvent>(UE_BIND_EVENT_FN(OnGamepadButtonReleased));
	}

	void EditorLayer::RegisterWindowEvent(std::function<bool(Event&)>& fn)
	{
		m_WindowEventFns.push_back(fn);
	}

	void EditorLayer::RegisterInputEvent(std::function<bool(Event&)>& fn)
	{
		m_InputEventFns.push_back(fn);
	}

	bool EditorLayer::OnWindowResize(WindowResizeEvent& event)
	{
		UE::Renderer3D::OnWindowResize(event.GetWidth(), event.GetHeight());
		return false;
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& event)
	{
		switch (event.GetKeyCode())
		{
		case UE::KeyCode::W:
			m_CameraController->MoveForward();
			break;
		case UE::KeyCode::S:
			m_CameraController->MoveBackward();
			break;
		case UE::KeyCode::A:
			m_CameraController->MoveLeft();
			break;
		case UE::KeyCode::D:
			m_CameraController->MoveRight();
			break;
		case UE::KeyCode::E:
			m_CameraController->MoveUp();
			break;
		case UE::KeyCode::Q:
			m_CameraController->MoveDown();
			break;
		}

		return false;
	}

	bool EditorLayer::OnKeyReleased(KeyReleasedEvent& event)
	{
		switch (event.GetKeyCode())
		{
		case UE::KeyCode::W:
			m_CameraController->StopForward();
			break;
		case UE::KeyCode::S:
			m_CameraController->StopForward();
			break;
		case UE::KeyCode::A:
			m_CameraController->StopRight();
			break;
		case UE::KeyCode::D:
			m_CameraController->StopRight();
			break;
		case UE::KeyCode::E:
			m_CameraController->StopUp();
			break;
		case UE::KeyCode::Q:
			m_CameraController->StopUp();
			break;
		}

		return false;
	}

	bool EditorLayer::OnKeyTyped(KeyTypedEvent& event)
	{
		return false;
	}

	bool MoveAround = false;

	bool EditorLayer::OnMousePressed(MouseButtonPressedEvent& event)
	{
		switch (event.GetMouseButton())
		{
		case UE::MouseCode::Right:
			MoveAround = true;
			break;
		}

		return false;
	}

	bool EditorLayer::OnMouseReleased(MouseButtonReleasedEvent& event)
	{
		switch (event.GetMouseButton())
		{
		case UE::MouseCode::Right:
			MoveAround = false;
			break;
		}

		return false;
	}

	float LastMouseX = 0;
	float LastMouseY = 0;

	bool EditorLayer::OnMouseMoved(MouseMovedEvent& event)
	{
		UE::Ref<UE::Camera> CurrentCamera = m_CameraController->GetCamera();

		int CurrentMouseX = (int)event.GetX();
		int CurrentMouseY = (int)event.GetY();

		int DiffMouseX = CurrentMouseX - (int)LastMouseX;
		int DiffMouseY = CurrentMouseY - (int)LastMouseY;

		LastMouseX = CurrentMouseX;
		LastMouseY = CurrentMouseY;

		if (MoveAround)
		{
			float CurrentYaw = CurrentCamera->GetYaw();
			float CurrentPitch = CurrentCamera->GetPitch();

			CurrentCamera->SetYaw(CurrentYaw + (DiffMouseX * 0.001f));
			CurrentCamera->SetPitch(CurrentPitch + (DiffMouseY * 0.001f));
		}

		return false;
	}

	bool EditorLayer::OnMouseScrolled(MouseScrolledEvent& event)
	{
		m_Camera->ZoomIn(event.GetXOffset() * 0.25f);

		return false;
	}

	bool EditorLayer::OnGamepadButtonPressed(GamepadButtonPressedEvent& event)
	{
		return false;
	}

	bool EditorLayer::OnGamepadButtonReleased(GamepadButtonReleasedEvent& event)
	{
		return false;
	}
}