#include "uepch.h"
#include "Core/Application.h"

#include "Renderer/Renderer.h"

#include "ECS/System.h"

// Todo: implement minify or iconify function inside OnWindowResize()

#include "Script/Lune/LuneModule.h"
#include "ECS/EntityLua.h"

#include "Script/LuneExposer.h"

#include "Renderer/Shader/ShaderHeaderConstructor.h"

namespace UE
{
	Application* Application::s_Instance = nullptr;

	Ref<EntityManager> m_EntityManager;

	struct PosXTest
	{
		float X;
	};

	Application::Application()
	{
		// Start the clock that provides the time
		m_Data->m_TimeMeasurer.Start();

		// Check current platform endianness
		UE_CORE_INFO("Platform is {0} endian", UE_IS_NATIVE_BIG_ENDIAN() ? "big" : "little");

		// Check if another instance is already running
		UE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// Create basic window and set engine event response
		m_Data->m_Window = Window::Create(WindowProps("UnnamedProject"));
		m_Data->m_Window->SetWindowEventCallback(UE_BIND_EVENT_FN(Application::OnWindowEvent));
		m_Data->m_Window->SetInputEventCallback(UE_BIND_EVENT_FN(Application::OnInputEvent));
		m_Data->m_Window->SetVSync(true);

		// Initialize the renderer
		Renderer::Init();

		// Initialize ImGui
		m_Data->m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_Data->m_ImGuiLayer);

		// Initialize Lua
		m_Data->m_Lune = CreateRef<LuneStack>();
		ExposeCoreToLune(m_Data->m_Lune);

		ComponentDataShell PosX("PositionX", UEType::Float, 512);
		PosX.SetData<UEFloat>(1, 0.5f);
		UE_CORE_INFO(PosX.GetData<UEFloat>(1));
	}

	Application::~Application()
	{
		Renderer::Shutdown();

		//LuaAPI::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::Close()
	{
		m_Data->m_Running = false;
	}

	void Application::Run()
	{
		#if defined(UE_PLATFORM_WINDOWS)
			while (m_Data->m_Running)
			{
				MainLoop();
			}

		#elif defined(UE_PLATFORM_WEB)
		#endif
	};

	bool Application::MainLoop()
	{
		m_Data->m_TimeMeasurer.End();
		float time = m_Data->m_TimeMeasurer.FormattedSeconds();
		Timestep timestep = (time - m_Data->m_LastFrameTime) * m_Data->m_SimulationSpeed;
		m_Data->m_LastFrameTime = time;

		if (!m_Data->m_Minimized)
		{
			// Update layers
			{
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(timestep);
				}
			}

			// Update imgui
			m_Data->m_ImGuiLayer->Begin();
			{
				for (Layer* layer : m_LayerStack)
				{
					layer->OnImGuiRender();
				}
			}
			m_Data->m_ImGuiLayer->End();
		}

		m_Data->m_Window->OnUpdate();

		return m_Data->m_Running;
	}

	void Application::OnWindowEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(UE_BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(UE_BIND_EVENT_FN(OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (event.m_Handled)
			{
				break;
			}
			(*it)->OnWindowEvent(event);
		}
	}

	void Application::OnInputEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(UE_BIND_EVENT_FN(OnKeyPressed));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); it++)
		{
			if (event.m_Handled)
			{
				break;
			}
			(*it)->OnInputEvent(event);
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Data->m_Minimized = false;
		m_Data->m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& event)
	{
		m_Data->m_Minimized = false;

		if (event.GetWidth() == 0 || event.GetHeight() == 0)
		{
			m_Data->m_Minimized = true;
			return false;
		}

		RenderCommand::SetViewport(0, 0, event.GetWidth(), event.GetHeight());

		return false;
	}

	bool Application::OnKeyPressed(KeyPressedEvent& event)
	{
		switch (event.GetKeyCode())
		{
		case KeyCode::Escape:
			m_Data->m_Running = false;
			break;
		case KeyCode::F11:
			m_Data->m_Fullscreen = !m_Data->m_Fullscreen;
			m_Data->m_Window->SetFullscreen(m_Data->m_Fullscreen);
			break;
		}
		return false;
	}
}