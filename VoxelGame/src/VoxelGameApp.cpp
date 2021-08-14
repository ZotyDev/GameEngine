#include "VoxelGameApp.h"

#include "World/ChunkManager.h"

VoxelGameApp::VoxelGameApp()
{
}

ChunkManager m_ChunkManager;

void VoxelGameApp::OnAttach()
{
	// Todo: 
	// Implement 2D renderer (GUI, etc)
	// Implement particles

	m_Texture2D = UE::Texture2D::Create("data/textures/grass.png");

	m_Camera = UE::Camera(1280, 720, glm::vec3(0.0f, 0.0f, 1.5f));
	m_CameraController = UE::CreateRef<UE::CameraController>(UE::CreateRef<UE::Camera>(m_Camera));

	UE::FramebufferSpecification specs;
	specs.Width = 1280;
	specs.Height = 720;
	specs.Attachments.Attachments.push_back(UE::FramebufferTextureSpecification(UE::FramebufferTextureFormat::Color));
	specs.Attachments.Attachments.push_back(UE::FramebufferTextureSpecification(UE::FramebufferTextureFormat::Depth));
	m_Framebuffer = UE::Framebuffer::Create(specs);

	m_Screen = UE::CreateRef<UE::Primitives::Quad>(glm::vec2(-1.0f, 1.0f), glm::vec2(1.0f, -1.0f));
	m_Quad = UE::CreateRef<UE::Primitives::Quad>(glm::vec2(-0.5f, 0.5f), glm::vec2(0.5f, -0.5f));	

	// LoadShader LUA function register
	UE::LuaAPI::RegisterFunction("LoadShader", [](lua_State* L)
		{
			UE::ShaderLibrary* t_ShaderLibrary = (UE::ShaderLibrary*)lua_touserdata(L, lua_upvalueindex(1));

			const char* t_FilePath = (const char*)lua_tostring(L, -1);

			t_ShaderLibrary->Load(t_FilePath);
			UE_INFO("Loaded texture: {0}", t_FilePath);

			return 1;
		}, (void*)m_ShaderLibrary.get());

	// Execute file that load the shaders
	UE::LuaAPI::ExecuteFile("data/mods/shaders.lua");

	UE::Renderer3D::Init(m_ShaderLibrary->Get("screen"), m_Framebuffer);

	// TEMPORARY CHUNK
	m_ChunkManager.AddChunk({ 0, 0, 0 });
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
	/*============================================================================*/

	UE::Renderer3D::DrawVao(m_Quad->VAO, m_Texture2D, m_ShaderLibrary->Get("default"), { 0.0f, 0.0f, 0.0f });
	UE::Renderer3D::DrawVao(m_Quad->VAO, m_Texture2D, m_ShaderLibrary->Get("default"), { 1.0f, 0.0f, 0.0f });
	UE::Renderer3D::DrawVao(m_Quad->VAO, m_Texture2D, m_ShaderLibrary->Get("default"), { 0.0f, 1.0f, 0.0f });
	UE::Renderer3D::DrawVao(m_Quad->VAO, m_Texture2D, m_ShaderLibrary->Get("default"), { 0.0f, 0.0f, 1.0f });
	UE::Renderer3D::DrawVao(m_Quad->VAO, m_Texture2D, m_ShaderLibrary->Get("default"), { -1.0f, 0.0f, 0.0f });
	UE::Renderer3D::DrawVao(m_Quad->VAO, m_Texture2D, m_ShaderLibrary->Get("default"), { 0.0f, -1.0f, 0.0f });
	UE::Renderer3D::DrawVao(m_Quad->VAO, m_Texture2D, m_ShaderLibrary->Get("default"), { 0.0f, 0.0f, -1.0f });

	/*============================================================================*/
	UE::Renderer3D::EndRender();
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
	m_Framebuffer->Resize(event.GetWidth(), event.GetHeight());
	return false;
}

bool VoxelGameApp::OnKeyPressed(UE::KeyPressedEvent& event)
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

bool VoxelGameApp::OnMouseMoved(UE::MouseMovedEvent& event)
{
	m_CameraController->GetCamera()->SetYaw(event.GetX() * 0.001f);
	m_CameraController->GetCamera()->SetPitch(event.GetY() * 0.001f);
	return false;
}

bool VoxelGameApp::OnMouseScrolled(UE::MouseScrolledEvent& event)
{
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