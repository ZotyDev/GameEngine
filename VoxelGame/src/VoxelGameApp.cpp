#include "VoxelGameApp.h"

#include <imgui/imgui.h>

namespace UE
{
	VoxelGameApp::VoxelGameApp(Ref<Application::SharedData> data)
		: Layer("VoxelGameApp"), m_Data(data)
	{}

	Ref<Material> GrassMaterial = CreateRef<Material>();

	void VoxelGameApp::OnAttach()
	{
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
		Ref<Framebuffer> m_Framebuffer = Framebuffer::Create(specs);

		m_Quad = CreateRef<Primitives::Quad>(glm::vec2(-0.5f, 0.5f), glm::vec2(0.5f, -0.5f));

		// LoadShader LUA function register
		UE::LuneFunction LoadShader("LoadShader", [](lua_State* L) -> int
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

		m_Screen = CreateRef<UE::Screen>(m_ShaderLibrary->Get("screen"), m_Framebuffer);

		Renderer3D::Init(m_Screen);

		// TEMPORARY MATERIAL
		GrassMaterial->RegisterShader("Shader", m_ShaderLibrary->Get("default"));
		GrassMaterial->RegisterShader("Shadow", m_ShaderLibrary->Get("shadow"));
		GrassMaterial->RegisterTexture("Texture", m_Texture2D);
	}

	void VoxelGameApp::OnDetach()
	{
	}

	void VoxelGameApp::OnUpdate(Timestep timestep)
	{
		m_CameraController->OnUpdate(timestep);

		Render();
	}

	void VoxelGameApp::OnImGuiRender()
	{
		//ImGui::Begin("Settings");

		//ImGui::End();
	}

	void VoxelGameApp::Render()
	{
		Renderer3D::BeginRender(m_CameraController->GetCamera());
		/*============================================================================*/

		Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, 0.0f, 0.0f });
		Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 1.0f, 0.0f, 0.0f });
		Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, 1.0f, 0.0f });
		Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, 0.0f, 1.0f });
		Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { -1.0f, 0.0f, 0.0f });
		Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, -1.0f, 0.0f });
		Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, 0.0f, -1.0f });

		/*============================================================================*/
		Renderer3D::EndRender();
	}

	void VoxelGameApp::OnWindowEvent(Event& event)
	{
		m_CameraController->OnEvent(event);

		UE::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowResizeEvent>(UE_BIND_EVENT_FN(OnWindowResize));
	}

	void VoxelGameApp::OnInputEvent(Event& event)
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

	void VoxelGameApp::RegisterWindowEvent(std::function<bool(Event&)>& fn)
	{
		m_WindowEventFns.push_back(fn);
	}

	void VoxelGameApp::RegisterInputEvent(std::function<bool(Event&)>& fn)
	{
		m_InputEventFns.push_back(fn);
	}

	bool VoxelGameApp::OnWindowResize(WindowResizeEvent& event)
	{
		UE::Renderer3D::OnWindowResize(event.GetWidth(), event.GetHeight());
		return false;
	}

	bool VoxelGameApp::OnKeyPressed(KeyPressedEvent& event)
	{
		switch (event.GetKeyCode())
		{
		case UE::KeyCode::LeftAlt:
		{
			m_Data->m_Window->SetCursorHidden(false);
			m_Keyboard->SetState(KeyCode::LeftAlt, false);
			break;
		}
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

	bool VoxelGameApp::OnKeyReleased(KeyReleasedEvent& event)
	{
		switch (event.GetKeyCode())
		{
		case UE::KeyCode::LeftAlt:
		{
			m_Data->m_Window->SetCursorHidden(true);
			m_Keyboard->SetState(KeyCode::LeftAlt, true);
			break;
		}
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

	bool VoxelGameApp::OnKeyTyped(KeyTypedEvent& event)
	{
		return false;
	}

	bool VoxelGameApp::OnMousePressed(MouseButtonPressedEvent& event)
	{
		return false;
	}

	bool VoxelGameApp::OnMouseReleased(MouseButtonReleasedEvent& event)
	{
		return false;
	}

	float LastMouseX = 0;
	float LastMouseY = 0;

	bool VoxelGameApp::OnMouseMoved(MouseMovedEvent& event)
	{
		UE::Ref<UE::Camera> CurrentCamera = m_CameraController->GetCamera();

		int CurrentMouseX = (int)event.GetX();
		int CurrentMouseY = (int)event.GetY();

		int DiffMouseX = CurrentMouseX - (int)LastMouseX;
		int DiffMouseY = CurrentMouseY - (int)LastMouseY;

		LastMouseX = CurrentMouseX;
		LastMouseY = CurrentMouseY;

		if (m_Keyboard->GetState(UE::KeyCode::LeftAlt))
		{
			float CurrentYaw = CurrentCamera->GetYaw();
			float CurrentPitch = CurrentCamera->GetPitch();

			CurrentCamera->SetYaw(CurrentYaw + (DiffMouseX * 0.001f));
			CurrentCamera->SetPitch(CurrentPitch + (DiffMouseY * 0.001f));
		}

		return false;
	}

	bool VoxelGameApp::OnMouseScrolled(MouseScrolledEvent& event)
	{
		m_Camera->ZoomIn(event.GetXOffset() * 0.25f);

		return false;
	}

	bool VoxelGameApp::OnGamepadButtonPressed(GamepadButtonPressedEvent& event)
	{
		return false;
	}

	bool VoxelGameApp::OnGamepadButtonReleased(GamepadButtonReleasedEvent& event)
	{
		return false;
	}
}