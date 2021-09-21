#include "VoxelGameApp.h"

#include "World/ChunkManager.h"

VoxelGameApp::VoxelGameApp(UE::Ref<UE::Window> masterWindow, bool* running, bool* minimized)
	: m_MasterWindow(masterWindow), m_Running(running), m_Minimized(minimized)
{}

ChunkManager m_ChunkManager;

UE::Ref<UE::Material> GrassMaterial = UE::CreateRef<UE::Material>();

void VoxelGameApp::OnAttach()
{
	// Todo: 
	// Implement 2D renderer (GUI, etc)
	// Implement particles

	m_Texture2D = UE::Texture2D::Create("data/textures/grass.png");

	m_Camera = UE::CreateRef<UE::Camera2D>(1280, 720, glm::vec3(0.0f, 0.0f, 1.5f));
	m_CameraController = UE::CreateRef<UE::CameraController>(m_Camera);

	UE::FramebufferSpecification specs;
	specs.Width = 1280;
	specs.Height = 720;
	specs.Attachments.Attachments.push_back(UE::FramebufferTextureSpecification(UE::FramebufferTextureFormat::Color));
	specs.Attachments.Attachments.push_back(UE::FramebufferTextureSpecification(UE::FramebufferTextureFormat::Depth));
	m_Framebuffer = UE::Framebuffer::Create(specs);

	m_Quad = UE::CreateRef<UE::Primitives::Quad>(glm::vec2(-0.5f, 0.5f), glm::vec2(0.5f, -0.5f));

	// LoadShader LUA function register
	UE::LuaAPI::RegisterFunction("LoadShader", [](lua_State* L)
		{
			UE::ShaderLibrary* t_ShaderLibrary = (UE::ShaderLibrary*)lua_touserdata(L, lua_upvalueindex(1));

			const char* t_FilePath = (const char*)lua_tostring(L, -1);

			t_ShaderLibrary->Load(t_FilePath);
			UE_INFO("Loaded shader: {0}", t_FilePath);

			return 1;
		}, (void*)m_ShaderLibrary.get());

	// RegisterMessagesLayout LUA function register
	UE::LuaAPI::RegisterFunction("RegisterMessagesLayout", [](lua_State* L)
		{
			UE::MessageLayoutLibrary* l_MessageLayoutLibrary = (UE::MessageLayoutLibrary*)lua_touserdata(L, lua_upvalueindex(1));

			if (lua_istable(L, -1) == false)
			{
				UE_LUA_ERROR("RegisterMessagesLayout failed: object is not table");
				return 1;
			}

			lua_pushnil(L);
			while (lua_next(L, -2) != 0)
			{
				char* LayoutName;
				UE::LuaGetString(L, -2, LayoutName);
				UE_LUA_INFO("{0}:", lua_tostring(L, -2));

				UE::MessageLayout CurrentMessageLayout;

				lua_pushnil(L);
				while (lua_next(L, -2) != 0)
				{

					UE::UEVValue MyVar;
					switch (lua_type(L, -1))
					{
					case LUA_TNIL:
						break;
					case LUA_TBOOLEAN:
						MyVar.Type = UE::UEType::Bool;
						UE::LuaGetString(L, -2, MyVar.Name);
						UE::LuaGetBoolean(L, -1, MyVar.Bool);
						CurrentMessageLayout.Elements.push_back(MyVar);
						UE_LUA_INFO("	{0} : {1}", lua_tostring(L, -2), MyVar.Bool);
						break;
					case LUA_TNUMBER:
						MyVar.Type = UE::UEType::Double;
						UE::LuaGetString(L, -2, MyVar.Name);
						UE::LuaGetNumber(L, -1, MyVar.Double);
						CurrentMessageLayout.Elements.push_back(MyVar);
						UE_LUA_INFO("	{0} : {1}", lua_tostring(L, -2), MyVar.Double);
						break;
					case LUA_TSTRING:
						MyVar.Type = UE::UEType::String;
						UE::LuaGetString(L, -2, MyVar.Name);
						UE::LuaGetString(L, -1, MyVar.String);
						CurrentMessageLayout.Elements.push_back(MyVar);
						UE_LUA_INFO("	{0} : {1}", lua_tostring(L, -2), MyVar.String);
						break;
					}

					lua_pop(L, 1);
				}

				l_MessageLayoutLibrary->RegisterMessageLayout(LayoutName, UE::CreateRef<UE::MessageLayout>(CurrentMessageLayout));

				lua_pop(L, 1);
			}

			return 1;
		}, (void*)m_MessageLayoutLibrary.get());

	// Execute file that load the shaders
	UE::LuaAPI::ExecuteFile("data/mods/shaders.lua");
	UE::LuaAPI::ExecuteFile("data/mods/messages.lua");

	UE_LUA_INFO("Stack size is {0}", lua_gettop(UE::LuaAPI::GetLua()));

	UE::Renderer3D::Init(m_ShaderLibrary->Get("screen"), m_Framebuffer);

	// TEMPORARY CHUNK
	m_ChunkManager.AddChunk({ 0, 0, 0 });

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

	int CurrentMouseX = event.GetX();
	int CurrentMouseY = event.GetY();

	int DiffMouseX = CurrentMouseX - LastMouseX;
	int DiffMouseY = CurrentMouseY - LastMouseY;
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