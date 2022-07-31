#include "EditorLayer.h"

#include <imgui.h>
#include <imgui_internal.h>

#include "Panels/PanelsConfig.h"
#include "ProjectConfig.h"

#include "Debug/Instrumentator.h"

namespace UE
{
	EditorLayer::EditorLayer(Ref<Application::SharedData> data)
		: Layer("EditorLayer"), m_Data(data)
	{}

	Ref<Material> GrassMaterial = CreateRef<Material>();

	EntityManager m_EntityManager;

	void EditorLayer::OnAttach()
	{
		PanelsConfig::LoadConfigs();
		ProjectConfig::LoadConfigs();

		UE_INFO("Current project:\n Name: {0}\n Location: {1}\n CurrentDirectory: {2}", 
			ProjectConfig::ProjectName, 
			ProjectConfig::ProjectLocation,
			ProjectConfig::CurrentDirectory);

		// Set the icon for the game window
		m_Data->m_Window->SetIcon("res/icon.png");

		m_Texture2D = Texture2D::Create();
		const UEString TexturePath = "assets/textures/grass.png";
		if (m_Texture2D->LoadFromSource(TexturePath) == UEResult::Error)
		{
			UE_ERROR("Failed to load {0}: not found", TexturePath);
		}

		m_Camera = CreateRef<Camera3D>(
			GlobalConfig::Rendering::ScreenWidth, 
			GlobalConfig::Rendering::ScreenHeight, 
			glm::vec3(0.0f, 0.0f, 1.5f));
		m_CameraController = CreateRef<CameraController>(m_Camera);

		FramebufferSpecification specs;
		specs.Width = GlobalConfig::Rendering::DesiredWidth;
		specs.Height = GlobalConfig::Rendering::DesiredHeight;
		specs.Samples = 4;
		specs.Attachments = { FramebufferTextureFormat::Color, FramebufferTextureFormat::Depth };
		Ref<Framebuffer> tFramebuffer = Framebuffer::Create(specs);

		specs.Width = GlobalConfig::Rendering::DesiredWidth;
		specs.Height = GlobalConfig::Rendering::DesiredHeight;
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

		Renderer3D::Init(m_Screen);

		ShaderHeaderConstructor MyShaderHeaderConstructor("assets/shaders/default");
		std::vector<ShaderHeaderConstructor::Element> tShaderElements;

		tShaderElements.push_back({
			"Position",
			ShaderDataType::Vec3,
			ShaderHeaderConstructor::UseType::VertInput,
			});

		tShaderElements.push_back({
			"Texture",
			ShaderDataType::Vec2,
			ShaderHeaderConstructor::UseType::VertInput,
			});

		tShaderElements.push_back({
			"Texture",
			ShaderDataType::Vec2,
			ShaderHeaderConstructor::UseType::VertOutput,
			});

		tShaderElements.push_back({
			"FragColor",
			ShaderDataType::Vec4,
			ShaderHeaderConstructor::UseType::FragOutput,
			});

		tShaderElements.push_back({
			"Transform",
			ShaderDataType::Mat4,
			ShaderHeaderConstructor::UseType::VertUniform,
			});

		tShaderElements.push_back({
			"Albedo",
			ShaderDataType::Sampler2D,
			ShaderHeaderConstructor::UseType::FragSampler,
			});

		MyShaderHeaderConstructor.SetElements(tShaderElements);

		UEString NewVertSource;
		UEString NewFragSource;
		MyShaderHeaderConstructor.Construct(NewVertSource, NewFragSource);

		ShaderLibrary::Get("default")->Set(NewVertSource, NewFragSource);
		GrassMaterial->RegisterShader("Shader", ShaderLibrary::Get("default"));
		GrassMaterial->RegisterTexture("Texture", m_Texture2D);
	}
	
	void EditorLayer::OnDetach()
	{
		
	}

	void EditorLayer::OnUpdate(Timestep timestep)
	{
		{
			UE_PROFILE_SCOPE("EditorLayer Update");
			m_CameraController->OnUpdate(timestep);
		}
		
		// Rendering
		{
			UE_PROFILE_SCOPE("Rendering");
			Renderer::BeginRender(m_CameraController->GetCamera());
			Render();
			Renderer::EndRender();
		}
	}

	void EditorLayer::Render()
	{
		Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, 0.0f, 0.0f });
		Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 1.0f, 0.0f, 0.0f });
		Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, 1.0f, 0.0f });
		Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, 0.0f, 1.0f });
		Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { -1.0f, 0.0f, 0.0f });
		Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, -1.0f, 0.0f });
		Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, 0.0f, -1.0f });
	}

	void EditorLayer::OnImGuiRender()
	{
		UE_PROFILE_SCOPE("ImGui Rendering");
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
		m_ViewportPanel.OnImGuiRender(m_Data, m_Screen->m_ViewportBounds, &m_Screen->m_ViewportSize, m_Screen->m_IntFramebuffer);
		m_ContentBrowserPanel.OnImGuiRender();
		m_SceneHierarchyPanel.OnImGuiRender();
		m_PropertiesPanel.OnImGuiRender();
		m_ProfilerPanel.OnImGuiRender();
		
		ImGui::End();

		auto Pos = m_Camera->GetPosition();
		
		ImGui::Begin("Debug");
		
		ImGui::Text("X: %f", Pos.x);
		ImGui::Text("Y: %f", Pos.y);
		ImGui::Text("Zoom: %f", m_Camera->GetZoom());
		ImGui::Text("Width: %i", GlobalConfig::Application::Width);
		ImGui::Text("Height: %i", GlobalConfig::Application::Height);
		ImGui::Text("Rendering Screen Width: %i", GlobalConfig::Rendering::ScreenWidth);
		ImGui::Text("Rendering Screen Height: %i", GlobalConfig::Rendering::ScreenHeight);
		ImGui::Text("Pixel Size: %f", GlobalConfig::Rendering::PixelSize);
		ImGui::Text("Rendering Width: %i", m_Screen->m_Framebuffer->GetWidth());
		ImGui::Text("Rendering Height: %i", m_Screen->m_Framebuffer->GetHeight());
		UEUint32 ViewportX = 0;
		UEUint32 ViewportY = 0;
		RenderCommand::GetViewport(ViewportX, ViewportY);
		ImGui::Text("ViewportWidth: %i", ViewportX);
		ImGui::Text("Viewportheight: %i", ViewportY);

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
		case UE::KeyCode::Up:
			GlobalConfig::Rendering::PixelSize *= 2;
			OnRendererScaleChange(RendererScaleChangeEvent());
			break;
		case UE::KeyCode::Down:
			GlobalConfig::Rendering::PixelSize /= 2;
			OnRendererScaleChange(RendererScaleChangeEvent());
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

			CurrentCamera->SetYaw(CurrentYaw + (DiffMouseX * 0.001f * GlobalConfig::Mouse::MovementSensibilityX));
			CurrentCamera->SetPitch(CurrentPitch + (DiffMouseY * 0.001f * GlobalConfig::Mouse::MovementSensibilityY));
		}

		return false;
	}

	bool EditorLayer::OnMouseScrolled(MouseScrolledEvent& event)
	{
		m_Camera->ZoomIn(event.GetXOffset() * 0.25f * GlobalConfig::Mouse::ScrollSensibilityX);

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

	bool EditorLayer::OnRendererScaleChange(RendererScaleChangeEvent& event)
	{
		GlobalConfig::Rendering::DesiredWidth = (UEUint32)((UEFloat)GlobalConfig::Rendering::ScreenWidth / GlobalConfig::Rendering::PixelSize);
		GlobalConfig::Rendering::DesiredHeight = (UEUint32)((UEFloat)GlobalConfig::Rendering::ScreenHeight / GlobalConfig::Rendering::PixelSize);

		Renderer::OnWindowResize();

		return false;
	}
}