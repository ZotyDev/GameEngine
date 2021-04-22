#include "Application.h"

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/Camera3D.h"
#include "Renderer/Framebuffer.h"
#include "Renderer/Primitives.h"

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

namespace UE
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	Window* window;

	Ref<ShaderLibrary> m_ShaderLibrary = CreateRef<ShaderLibrary>();
	
	Ref<Texture2D> m_Texture2D;

	Camera3D m_Camera;

	Ref<Framebuffer> m_Framebuffer;

	Ref<Primitives::Quad> m_Screen;
	Ref<Primitives::Quad> m_Quad;

	void Application::Run()
	{
		// LUA TESTING

		std::string cmd = "a = 7 + 11";

		lua_State* L = luaL_newstate();

		int r = luaL_dostring(L, cmd.c_str());
		
		if (r == LUA_OK)
		{
			lua_getglobal(L, "a");
			if (lua_isnumber(L, -1))
			{
				float a_in_cpp = (float)lua_tonumber(L, -1);
				UE_LOG_INFO("Execute victory dance! The result is ", a_in_cpp);
			}
		}
		else
		{
			std::string errormsg = lua_tostring(L, -1);
			UE_LOG_INFO(errormsg);
		}

		lua_close(L);

		// LUA TESTING

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

		m_Screen = CreateRef<Primitives::Quad>(glm::vec2(-1.0f, 1.0f), glm::vec2(1.0f, -1.0f));
		m_Quad = CreateRef<Primitives::Quad>(glm::vec2(-0.5f, 0.5f), glm::vec2(0.5f, -0.5f));

		m_ShaderLibrary->Load("data/shaders/default");
		m_ShaderLibrary->Load("data/shaders/screen");

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

		m_Camera.Update();
	};

	void Application::Render()
	{
		m_Framebuffer->Bind();
		Renderer::BeginRender(m_Camera);
		
		m_Texture2D->Bind();
		Renderer::Submit(m_ShaderLibrary->Get("default"), m_Quad->VAO);

		m_Framebuffer->Unbind();
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glBindTexture(GL_TEXTURE_2D, m_Framebuffer->GetColorAttachmentRendererID());
		Renderer::Submit(m_ShaderLibrary->Get("screen"), m_Screen->VAO);

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

		m_Framebuffer->Resize(event.GetWidth(), event.GetHeight());

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