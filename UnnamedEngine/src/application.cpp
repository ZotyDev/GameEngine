#include "Application.h"

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/Camera3D.h"
#include "Renderer/Framebuffer.h"

namespace UE
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	Window* window;

	Ref<VertexBuffer> vBuffer;
	Ref<IndexBuffer> iBuffer;
	Ref<VertexArray> vArray;

	Ref<ShaderLibrary> m_ShaderLibrary = CreateRef<ShaderLibrary>();
	
	Ref<Texture2D> m_Texture2D;

	Camera3D m_Camera;

	Ref<Framebuffer> m_Framebuffer;

	Ref<VertexBuffer> screenVBuffer;
	Ref<IndexBuffer> screenIBuffer;
	Ref<VertexArray> screenVArray;

	void Application::Run()
	{
		LocalTime::Update();

		window = new WindowsWindow();
		window->Initialize("UnnamedEngine", 1280, 720);
		Renderer::Init();
		window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		m_Texture2D = Texture2D::Create("data/textures/grass.png");

		m_Camera = Camera3D(1280, 720, glm::vec3(0.0f, 0.0f, 1.5f));

		FramebufferSpecification specs;
		specs.Width = 1280;
		specs.Height = 720;
		specs.Attachments.Attachments.push_back(FramebufferTextureSpecification(FramebufferTextureFormat::Color));
		m_Framebuffer = Framebuffer::Create(specs);

		vArray.reset(VertexArray::Create());
		screenVArray.reset(VertexArray::Create());

		// Plane
		float vertices[4 * 9] =
		{
			-0.5f,  0.5f, 0.0f,   0.5f, 0.7f, 0.4f, 1.0f,   0.0f, 1.0f,
			-0.5f, -0.5f, 0.0f,   0.8f, 0.8f, 0.2f, 1.0f,   0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,   0.2f, 0.3f, 0.8f, 1.0f,   1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,   0.8f, 0.2f, 0.8f, 1.0f,   1.0f, 1.0f
		};
		vBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout =
		{
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
			{ShaderDataType::Float2, "a_Texture"}
		};
		vBuffer->SetLayout(layout);
		vArray->AddVertexBuffer(vBuffer);
		uint32_t indices[] = { 0, 1, 3, 1, 2, 3};
		iBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		vArray->AddIndexBuffer(iBuffer);

		// Screen
		float screen[4 * 4] =
		{
			-1.0f,  1.0f,   0.0f, 1.0f,
			-1.0f, -1.0f,   0.0f, 0.0f,
			 1.0f, -1.0f,   1.0f, 0.0f,
			 1.0f,  1.0f,   1.0f, 1.0f
		};
		screenVBuffer.reset(VertexBuffer::Create(screen, sizeof(screen)));
		BufferLayout screenLayout =
		{
			{ShaderDataType::Float2, "a_Position"},
			{ShaderDataType::Float2, "a_Texture"}
		};
		screenVBuffer->SetLayout(screenLayout);
		screenVArray->AddVertexBuffer(screenVBuffer);
		screenIBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		screenVArray->AddIndexBuffer(screenIBuffer);

		m_ShaderLibrary->Load("data/shaders/default");
		m_ShaderLibrary->Get("default")->SetInt("texture1", 0);

		m_ShaderLibrary->Load("data/shaders/screen");
		m_ShaderLibrary->Get("screen")->SetInt("texture1", 0);

		while (m_Running)
		{
			Update();
			
			if (!m_Minimized)
			{
				Render();
			}
		}

		glfwDestroyWindow((GLFWwindow*)window->GetNativeWindow());
		glfwTerminate();
	};

	void Application::Update()
	{
		glfwPollEvents();

		Logger::ShowLog("tatest.log");

		//m_Camera->SetPitch(m_Camera->GetPitch() + 0.01f);
		//UE_LOG_INFO("Pitch ", m_Camera->GetPitch());
		m_Camera.Update();
	};

	void Application::Render()
	{
		Renderer::BeginRender(m_Camera);
		m_Framebuffer->Bind();
		glClearColor(0.1f, 0.1, 0.1f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		m_Texture2D->Bind();
		Renderer::Submit(m_ShaderLibrary->Get("default"), vArray);

		m_Framebuffer->Unbind();
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glBindTexture(GL_TEXTURE_2D, m_Framebuffer->GetColorAttachmentRendererID());
		Renderer::Submit(m_ShaderLibrary->Get("screen"), screenVArray);

		glfwSwapBuffers((GLFWwindow*)window->GetNativeWindow());
	};

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyPressedEvent>(std::bind(&Application::OnKeyPressed, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyReleasedEvent>(std::bind(&Application::OnKeyReleased, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyTypedEvent>(std::bind(&Application::OnKeyTyped, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&Application::OnMousePressed, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(std::bind(&Application::OnMouseReleased, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseMovedEvent>(std::bind(&Application::OnMouseMoved, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&Application::OnMouseScrolled, this, std::placeholders::_1));
		dispatcher.Dispatch<GamepadButtonPressedEvent>(std::bind(&Application::OnGamepadButtonPressed, this, std::placeholders::_1));
		dispatcher.Dispatch<GamepadButtonReleasedEvent>(std::bind(&Application::OnGamepadButtonReleased, this, std::placeholders::_1));
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Minimized = false;
		m_Running = false;
		return false;
	}

	bool Application::OnWindowResize(WindowResizeEvent& event)
	{
		m_Minimized = false;

		if (event.GetWidth() == 0 || event.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());

		m_Camera.SetViewportSize(event.GetWidth(), event.GetHeight());

		return false;
	}

	bool Application::OnKeyPressed(KeyPressedEvent& event)
	{
		return false;
	}

	bool Application::OnKeyReleased(KeyReleasedEvent& event)
	{
		return false;
	}

	bool Application::OnKeyTyped(KeyTypedEvent& event)
	{
		return false;
	}

	bool Application::OnMousePressed(MouseButtonPressedEvent& event)
	{
		return false;
	}

	bool Application::OnMouseReleased(MouseButtonReleasedEvent& event)
	{
		return false;
	}

	bool Application::OnMouseMoved(MouseMovedEvent& event)
	{
		return false;
	}

	bool Application::OnMouseScrolled(MouseScrolledEvent& event)
	{
		return false;
	}

	bool Application::OnGamepadButtonPressed(GamepadButtonPressedEvent& event)
	{
		return false;
	}

	bool Application::OnGamepadButtonReleased(GamepadButtonReleasedEvent& event)
	{
		return false;
	}
}