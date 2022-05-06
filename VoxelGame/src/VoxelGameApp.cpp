#include "VoxelGameApp.h"

#include <imgui/imgui.h>

#include "World/Chunk.h"

namespace UE
{
	VoxelGameApp::VoxelGameApp(Ref<Application::SharedData> data)
		: Layer("VoxelGameApp"), m_Data(data)
	{}

	Ref<Material> GrassMaterial = CreateRef<Material>();

	void VoxelGameApp::OnAttach()
	{
		m_Texture2D = Texture2D::Create();
		const UEPath TexturePath = "assets/textures/grass.png";
		if (m_Texture2D->LoadFromSource(TexturePath, (Texture::TextureFlags)(Texture::TextureFlags::FILTERING_NEAREST | Texture::TextureFlags::CLAMP_TO_EDGE)) == UEResult::Error)
		{
			UE_ERROR("Failed to load {0}: not found", TexturePath);
		}

		// Start the camera centered using offset
		UEInt32 CameraX = (UEInt32)GlobalConfig::Rendering::DesiredWidth / -2;
		UEInt32 CameraY = (UEInt32)GlobalConfig::Rendering::DesiredHeight / -2;

		m_Camera = CreateRef<Camera3D>(
			GlobalConfig::Rendering::ScreenWidth,
			GlobalConfig::Rendering::ScreenHeight, 
			glm::vec3(0.0f, 0.0f, 1.5f));
		//m_Camera->SetPositionOffset({ (UEFloat)CameraX, (UEFloat)CameraY, 0.0f });
		m_CameraController = CreateRef<CameraController>(m_Camera);

		FramebufferSpecification specs;
		specs.Width = GlobalConfig::Rendering::DesiredWidth;
		specs.Height = GlobalConfig::Rendering::DesiredHeight;
		specs.Samples = 1;
		specs.Attachments = { FramebufferTextureFormat::Color, FramebufferTextureFormat::Depth };
		Ref<Framebuffer> tFramebuffer = Framebuffer::Create(specs);

		specs.Samples = 1;
		specs.Attachments = { FramebufferTextureFormat::Color };
		Ref<Framebuffer> yFramebuffer = Framebuffer::Create(specs);

		//UEFloat TexX = (UEFloat)m_Texture2D->GetWidth();
		//UEFloat TexY = (UEFloat)m_Texture2D->GetHeight();
		//m_Quad = CreateRef<Primitives::Quad>(glm::vec2(0.0f, TexY), glm::vec2(TexX, 0.0f));
		m_Quad = CreateRef<Primitives::Quad>(glm::vec2(-0.5f, 0.5f), glm::vec2(0.5f, -0.5f));

		// LoadShader LUA function register
		LuneFunction LoadShader("LoadShader", [](lua_State* L) -> int
			{
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

	void VoxelGameApp::OnDetach()
	{
	}

	void VoxelGameApp::OnUpdate(Timestep timestep)
	{
		m_CameraController->OnUpdate(timestep);

		// Rendering
		Renderer::BeginRender(m_CameraController->GetCamera());
		Render();
		Renderer::EndRender();
	}

	void VoxelGameApp::Render()
	{
		Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, 0.0f, 0.0f });
		Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 1.0f, 0.0f, 0.0f });
		Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, 1.0f, 0.0f });
		Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, 0.0f, 1.0f });
		Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { -1.0f, 0.0f, 0.0f });
		Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, -1.0f, 0.0f });
		Renderer3D::Submit(m_Quad->VAO, GrassMaterial, { 0.0f, 0.0f, -1.0f });
	}

	void VoxelGameApp::OnImGuiRender()
	{
		//auto Pos = m_Camera->GetPosition();
		//
		//ImGui::Begin("Debug");
		//
		//ImGui::Text("X: %f", Pos.x);
		//ImGui::Text("Y: %f", Pos.y);
		//ImGui::Text("Zoom: %f", m_Camera->GetZoom());
		//ImGui::Text("Width: %i", GlobalConfig::Application::Width);
		//ImGui::Text("Height: %i", GlobalConfig::Application::Height);
		//ImGui::Text("Pixel Size: %f", GlobalConfig::Rendering::PixelSize);
		//ImGui::Text("Rendering Width: %i", m_Screen->m_Framebuffer->GetWidth());
		//ImGui::Text("Rendering Height: %i", m_Screen->m_Framebuffer->GetHeight());
		//UEUint32 ViewportX = 0;
		//UEUint32 ViewportY = 0;
		//RenderCommand::GetViewport(ViewportX, ViewportY);
		//ImGui::Text("ViewportWidth: %i", ViewportX);
		//ImGui::Text("Viewportheight: %i", ViewportY);
		//
		//ImGui::End();
	}

	void VoxelGameApp::OnWindowEvent(Event& event)
	{
		m_CameraController->OnEvent(event);

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowResizeEvent>(UE_BIND_EVENT_FN(OnWindowResize));
	}

	void VoxelGameApp::OnInputEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

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

	void VoxelGameApp::OnRendererEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<RendererScaleChangeEvent>(UE_BIND_EVENT_FN(OnRendererScaleChange));
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
		// Make sure the camera is always centered on the same point
		//UEInt32 NewCameraX = (UEInt32)GlobalConfig::Rendering::DesiredWidth / -2;
		//UEInt32 NewCameraY = (UEInt32)GlobalConfig::Rendering::DesiredHeight / -2;
		//m_Camera->SetPositionOffset({ (UEFloat)NewCameraX, (UEFloat)NewCameraY, 1.5f });

		return false;
	}

	bool VoxelGameApp::OnKeyPressed(KeyPressedEvent& event)
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

	bool VoxelGameApp::OnKeyReleased(KeyReleasedEvent& event)
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

	bool VoxelGameApp::OnKeyTyped(KeyTypedEvent& event)
	{
		return false;
	}

	bool MoveAround = false;

	bool VoxelGameApp::OnMousePressed(MouseButtonPressedEvent& event)
	{
		switch (event.GetMouseButton())
		{
		case UE::MouseCode::Right:
			MoveAround = true;
			break;
		}

		return false;
	}

	bool VoxelGameApp::OnMouseReleased(MouseButtonReleasedEvent& event)
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

	bool VoxelGameApp::OnMouseMoved(MouseMovedEvent& event)
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

	bool VoxelGameApp::OnMouseScrolled(MouseScrolledEvent& event)
	{
		m_Camera->ZoomIn(event.GetXOffset() * 0.25f * GlobalConfig::Zoom::SensibilityIn);

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

	bool VoxelGameApp::OnRendererScaleChange(RendererScaleChangeEvent& event)
	{
		GlobalConfig::Rendering::DesiredWidth = (UEUint32)((UEFloat)GlobalConfig::Rendering::ScreenWidth / GlobalConfig::Rendering::PixelSize);
		GlobalConfig::Rendering::DesiredHeight = (UEUint32)((UEFloat)GlobalConfig::Rendering::ScreenHeight / GlobalConfig::Rendering::PixelSize);

		Renderer::OnWindowResize();

		return false;
	}
}