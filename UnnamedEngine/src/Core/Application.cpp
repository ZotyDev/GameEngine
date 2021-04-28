#include "uepch.h"
#include "Core/Application.h"

#include "Renderer/Renderer.h"
#include "Script/LuaAPI.h"

#include <GLFW/glfw3.h>

#include <lua.h>

#include "Network/NetworkCommand.h"

namespace UE
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name)
	{
		Scope<std::string> test = CreateScope<std::string>();

		UE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = Window::Create(WindowProps(name));
		m_Window->SetEventCallback(UE_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();
		NetworkCommand::Init();
		LuaAPI::Init();
	}

	Application::~Application()
	{
		Renderer::Shutdown();
		LuaAPI::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(timestep);
				}
			}

			m_Window->OnUpdate();
		}
	};

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (event.m_Handled)
			{
				break;
			}
			(*it)->OnEvent(event);
		}

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
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& event)
	{
		m_Minimized = false;

		if (event.GetWidth() == 0 || event.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		RenderCommand::SetViewPort(0, 0, event.GetWidth(), event.GetHeight());

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