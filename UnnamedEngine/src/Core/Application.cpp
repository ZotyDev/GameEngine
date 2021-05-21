#include "uepch.h"
#include "Core/Application.h"

#include "Renderer/Renderer.h"
#include "Script/LuaAPI.h"

#include <GLFW/glfw3.h>

#include <lua.h>

#include "Network/NetworkCommand.h"
#include "Network/Packet.h"
#include "Network/Socket.h"

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
		/*NetworkCommand::Init();
		NetworkCommand::InitServer("27015");
		NetworkCommand::SetServerEventCallback(UE_BIND_EVENT_FN(Application::OnEvent));

		IPEndpoint ServerAddress("127.0.0.1", "27015");
		NetworkCommand::InitClient();
		NetworkCommand::Connect(ServerAddress);*/

		Message testMessage(0, MessageType::Invalid);
		std::string string = "hehehe i'm a text inside a message";
		uint32_t number = 1273623;

		testMessage << number;

		//std::string result = "";
		uint32_t resultN = 0;

		Packet myPacket(Packet::PacketType::MessagePacket);
		myPacket << testMessage;

		Message test1Message(0, MessageType::Invalid);
		myPacket >> test1Message;

		//test1Message >> result;
		test1Message >> resultN;

		UE_CORE_INFO("String: {0} - Number {0}", resultN);

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

	double last = 0;
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

				if (NetworkCommand::IsServer)
				{
					NetworkCommand::OnServerUpdate(timestep);
				}

				if (NetworkCommand::IsConnected)
				{
					NetworkCommand::OnClientUpdate(timestep);
				}
			}

			m_Window->OnUpdate();
		}
	};

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(UE_BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(UE_BIND_EVENT_FN(OnWindowResize));
		dispatcher.Dispatch<KeyPressedEvent>(UE_BIND_EVENT_FN(OnKeyPressed));
		dispatcher.Dispatch<ClientConnectedEvent>(UE_BIND_EVENT_FN(OnClientConnected));
		dispatcher.Dispatch<ClientDisconectedEvent>(UE_BIND_EVENT_FN(OnClientDisconnected));
		dispatcher.Dispatch<ClientMessageEvent>(UE_BIND_EVENT_FN(OnClientMessage));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (event.m_Handled)
			{
				break;
			}
			(*it)->OnEvent(event);
		}
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

		RenderCommand::SetViewport(0, 0, event.GetWidth(), event.GetHeight());

		return false;
	}

	bool IsCursorHidden = false;

	bool Application::OnKeyPressed(KeyPressedEvent& event)
	{
		switch (event.GetKeyCode())
		{
		case KeyCode::LeftAlt:
			if (IsCursorHidden)
			{
				glfwSetInputMode((GLFWwindow*)m_Window->GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				IsCursorHidden = !IsCursorHidden;
			}
			else
			{
				glfwSetInputMode((GLFWwindow*)m_Window->GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				IsCursorHidden = !IsCursorHidden;
			}
			break;
		case KeyCode::Escape:
			m_Running = false;
			break;
		}
		return false;
	}

	bool Application::OnClientConnected(ClientConnectedEvent& event)
	{
		UE_CORE_INFO("{0} connected!", event.GetAddress());
		return false;
	}

	bool Application::OnClientDisconnected(ClientDisconectedEvent& event)
	{
		UE_CORE_INFO("{0} disconnected!", event.GetAddress());
		return false;
	}

	bool Application::OnClientMessage(ClientMessageEvent& event)
	{
		UE_CORE_INFO("Message received!");
		return false;
	}
}