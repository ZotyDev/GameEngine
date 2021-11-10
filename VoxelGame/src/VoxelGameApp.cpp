#include "VoxelGameApp.h"

VoxelGameApp::VoxelGameApp(UE::Ref<UE::Window> masterWindow, bool* running, bool* minimized)
	: m_MasterWindow(masterWindow), m_Running(running), m_Minimized(minimized)
{}

UE::Ref<UE::Material> GrassMaterial = UE::CreateRef<UE::Material>();

void VoxelGameApp::OnAttach()
{
	// Todo: 
	// Implement 2D renderer (GUI, etc)
	// Implement particles

	m_Texture2D = UE::Texture2D::Create();
	const std::string TexturePath = "data/textures/grass.png";
	if (m_Texture2D->LoadFromSource(TexturePath) == UE::UEResult::Error)
	{
		UE_CORE_ERROR("Failed to load {0}: not found", TexturePath);
	}

	m_Camera = UE::CreateRef<UE::Camera3D>(1280, 720, glm::vec3(0.0f, 0.0f, 1.5f));
	m_CameraController = UE::CreateRef<UE::CameraController>(m_Camera);

	UE::FramebufferSpecification specs;
	specs.Width = 1280;
	specs.Height = 720;
	specs.Attachments.Attachments.push_back(UE::FramebufferTextureSpecification(UE::FramebufferTextureFormat::Color));
	specs.Attachments.Attachments.push_back(UE::FramebufferTextureSpecification(UE::FramebufferTextureFormat::Depth));
	m_Framebuffer = UE::Framebuffer::Create(specs);

	m_Quad = UE::CreateRef<UE::Primitives::Quad>(glm::vec2(-0.5f, 0.5f), glm::vec2(0.5f, -0.5f));

	UE::LuneStack LStack;

	// LoadShader LUA function register
	UE::LuneFunction LoadShader("LoadShader", [](lua_State* L) -> int 
		{
			UE::ShaderLibrary* t_ShaderLibrary = (UE::ShaderLibrary*)lua_touserdata(L, lua_upvalueindex(1));

			const char* t_FilePath = (const char*)lua_tostring(L, -1);

			t_ShaderLibrary->Load(t_FilePath);
			UE_INFO("Loaded shader: {0}", t_FilePath);

			return 1;
		});

	LoadShader.Register(LStack, (void*)m_ShaderLibrary.get());
	// Execute file that load the shaders
	LStack.ExecuteFile("data/mods/shaders.lua");
	//UE::LuaAPI::ExecuteFile("data/mods/messages.lua");

	UE_LUA_INFO("Stack size is {0}", LStack.GetTop());

	UE::Renderer3D::Init(m_ShaderLibrary->Get("screen"), m_Framebuffer);
	//UE::Renderer2D::Init(m_ShaderLibrary->Get("screen"), m_Framebuffer, m_ShaderLibrary->Get("quad"));

	// TEMPORARY MATERIAL
	GrassMaterial->RegisterShader("Shader", m_ShaderLibrary->Get("default"));
	GrassMaterial->RegisterShader("Shadow", m_ShaderLibrary->Get("shadow"));
	GrassMaterial->RegisterTexture("Texture", m_Texture2D);
}

void VoxelGameApp::OnDetach()
{
}

void VoxelGameApp::OnUpdate(UE::Timestep timestep)
{
	m_CameraController->OnUpdate(timestep);

	Render();
}

void VoxelGameApp::Render()
{
	UE::Renderer3D::BeginRender(m_CameraController->GetCamera());
//	UE::Renderer2D::BeginRender(m_CameraController->GetCamera());
	/*============================================================================*/

	UE::Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, 0.0f, 0.0f });
	UE::Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 1.0f, 0.0f, 0.0f });
	UE::Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, 1.0f, 0.0f });
	UE::Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, 0.0f, 1.0f });
	UE::Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { -1.0f, 0.0f, 0.0f });
	UE::Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, -1.0f, 0.0f });
	UE::Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, 0.0f, -1.0f });

	/*============================================================================*/
	UE::Renderer3D::EndRender();
//	UE::Renderer2D::EndRender();
}

void VoxelGameApp::OnEvent(UE::Event& event)
{
	m_CameraController->OnEvent(event);

	UE::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<UE::WindowResizeEvent>(UE_BIND_EVENT_FN(OnWindowResize));
	dispatcher.Dispatch<UE::KeyPressedEvent>(UE_BIND_EVENT_FN(OnKeyPressed));
	dispatcher.Dispatch<UE::KeyReleasedEvent>(UE_BIND_EVENT_FN(OnKeyReleased));
	dispatcher.Dispatch<UE::KeyTypedEvent>(UE_BIND_EVENT_FN(OnKeyTyped));
	dispatcher.Dispatch<UE::MouseButtonPressedEvent>(UE_BIND_EVENT_FN(OnMousePressed));
	dispatcher.Dispatch<UE::MouseButtonReleasedEvent>(UE_BIND_EVENT_FN(OnMouseReleased));
	dispatcher.Dispatch<UE::MouseMovedEvent>(UE_BIND_EVENT_FN(OnMouseMoved));
	dispatcher.Dispatch<UE::MouseScrolledEvent>(UE_BIND_EVENT_FN(OnMouseScrolled));
	dispatcher.Dispatch<UE::GamepadButtonPressedEvent>(UE_BIND_EVENT_FN(OnGamepadButtonPressed));
	dispatcher.Dispatch<UE::GamepadButtonReleasedEvent>(UE_BIND_EVENT_FN(OnGamepadButtonReleased));
}

bool VoxelGameApp::OnWindowResize(UE::WindowResizeEvent& event)
{
	UE::Renderer3D::OnWindowResize(event.GetWidth(), event.GetHeight());
	return false;
}

bool VoxelGameApp::OnKeyPressed(UE::KeyPressedEvent& event)
{
	switch (event.GetKeyCode())
	{
	case UE::KeyCode::LeftAlt:
	{
		bool CurrentState = m_Keyboard->GetState(UE::KeyCode::LeftAlt);
		m_MasterWindow->SetCursorHidden(!CurrentState);
		m_Keyboard->SetState(UE::KeyCode::LeftAlt, !CurrentState);
		break;
	}
	case UE::KeyCode::Escape:
		m_Running = false;
		break;
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

bool VoxelGameApp::OnKeyReleased(UE::KeyReleasedEvent& event)
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

bool VoxelGameApp::OnKeyTyped(UE::KeyTypedEvent& event)
{
	return false;
}

bool VoxelGameApp::OnMousePressed(UE::MouseButtonPressedEvent& event)
{
	return false;
}

bool VoxelGameApp::OnMouseReleased(UE::MouseButtonReleasedEvent& event)
{
	return false;
}

float LastMouseX = 0;
float LastMouseY = 0;

bool VoxelGameApp::OnMouseMoved(UE::MouseMovedEvent& event)
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

bool VoxelGameApp::OnMouseScrolled(UE::MouseScrolledEvent& event)
{
	m_Camera->ZoomIn(event.GetYOffset());

	return false;
}

bool VoxelGameApp::OnGamepadButtonPressed(UE::GamepadButtonPressedEvent& event)
{
	return false;
}

bool VoxelGameApp::OnGamepadButtonReleased(UE::GamepadButtonReleasedEvent& event)
{
	return false;
}