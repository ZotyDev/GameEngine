#include "VoxelGameApp.h"

VoxelGameApp::VoxelGameApp()
{
}

void VoxelGameApp::OnAttach()
{
	m_Texture2D = UE::Texture2D::Create("data/textures/grass.png");

	m_Camera = UE::Camera3D(1280, 720, glm::vec3(0.0f, 0.0f, 1.5f));
	m_CameraController = UE::CreateRef<UE::CameraController>(m_Camera);

	UE::FramebufferSpecification specs;
	specs.Width = 1280;
	specs.Height = 720;
	specs.Attachments.Attachments.push_back(UE::FramebufferTextureSpecification(UE::FramebufferTextureFormat::Color));
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
}

void VoxelGameApp::OnDetach()
{
}

void VoxelGameApp::OnUpdate(UE::Timestep timestep)
{
	m_CameraController->OnUpdate(timestep);

	// Rendering
	UE::Renderer3D::BeginRender(m_CameraController->GetCamera());

	m_Texture2D->Bind();
	UE::Renderer3D::Submit(m_ShaderLibrary->Get("default"), m_Quad->VAO);

	UE::Renderer3D::EndRender();
}

void VoxelGameApp::OnEvent(UE::Event& event)
{
	m_CameraController->OnEvent(event);

	UE::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<UE::WindowResizeEvent>(UE_BIND_EVENT_FN(OnWindowResize));
}

bool VoxelGameApp::OnWindowResize(UE::WindowResizeEvent& event)
{
	m_Framebuffer->Resize(event.GetWidth(), event.GetHeight());
	return false;
}