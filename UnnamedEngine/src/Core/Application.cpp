#include "uepch.h"
#include "Core/Application.h"

#include "Renderer/Renderer.h"

#include "ECS/System.h"

// Todo: implement minify or iconify function inside OnWindowResize()

#include "Script/Lune/LuneModule.h"
#include "ECS/EntityLua.h"

#include "Script/LuneExposer.h"

#include "Math/Random/RNGStrong.h"
#include "Math/Random/RNGFast.h"

namespace UE
{
	Application* Application::s_Instance = nullptr;

	Ref<EntityManager> m_EntityManager;

	Application::Application()
	{
		m_Data.m_TimeMeasurer.Start();

		UE_CORE_INFO("Platform is {0} endian", UE_IS_NATIVE_BIG_ENDIAN() ? "big" : "little");

		UE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Data.m_Window = Window::Create(WindowProps("UnnamedProject"));
		m_Data.m_Window->SetWindowEventCallback(UE_BIND_EVENT_FN(Application::OnWindowEvent));
		m_Data.m_Window->SetInputEventCallback(UE_BIND_EVENT_FN(Application::OnInputEvent));
		m_Data.m_Window->SetVSync(true);
		m_Data.m_Window->SetIcon("res/icon.png");

		Renderer::Init();

		Uint32RNGStrong Test(0, UE_UINT32_MAX);

		Stopwatch Timer;
		Timer.Start();
		for (UEUint32 i = 0; i < 1000; i++)
		{
			Test();
		}
		Timer.End();
		UE_CORE_INFO("{0}", Timer.FormattedMilliseconds());

		Timer.Start();
		for (UEUint32 i = 0; i < 1000; i++)
		{
			UEUint32 x = 123456789;
			UEUint32 y = 362436069;
			UEUint32 z = 521288629;
			UEUint32 w = 88675123;
			UEUint32 t = x ^ (x << 11);
			x = y;
			y = z;
			z = w;
			w = w ^ (w >> 19) ^ (t ^ (t >> 8));
		}

		Timer.End();
		UE_CORE_INFO("{0}", Timer.FormattedMilliseconds());

		m_Data.m_Lune = CreateRef<LuneStack>();

		ExposeCoreToLune(m_Data.m_Lune);

		//
		//Luna.Dump();
		//
		m_Data.m_Lune->ExecuteFile("data/mods/test.lua");
		//Luna.ExecuteFile("data/core/lua/CoreFunctionality.lua");


		m_Data.m_Window->IsVSync();
	}

	Application::~Application()
	{
		Renderer::Shutdown();

		//LuaAPI::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_Data.m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::Close()
	{
		m_Data.m_Running = false;
	}

	double last = 0;
	void Application::Run()
	{
		while (m_Data.m_Running)
		{
			m_Data.m_TimeMeasurer.End();
			float time = m_Data.m_TimeMeasurer.FormattedSeconds();
			Timestep timestep = (time - m_Data.m_LastFrameTime) * m_Data.m_SimulationSpeed;
			m_Data.m_LastFrameTime = time;

			if (!m_Data.m_Minimized)
			{
				// Update layers
				for (Layer* layer : m_Data.m_LayerStack)
				{
					layer->OnUpdate(timestep);
				}
			}

			m_Data.m_Window->OnUpdate();
		}
	};

	void Application::OnWindowEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(UE_BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(UE_BIND_EVENT_FN(OnWindowResize));

		for (auto it = m_Data.m_LayerStack.rbegin(); it != m_Data.m_LayerStack.rend(); ++it)
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

		for (auto it = m_Data.m_LayerStack.rbegin(); it != m_Data.m_LayerStack.rend(); it++)
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
		m_Data.m_Minimized = false;
		m_Data.m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& event)
	{
		m_Data.m_Minimized = false;

		if (event.GetWidth() == 0 || event.GetHeight() == 0)
		{
			m_Data.m_Minimized = true;
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
			m_Data.m_Running = false;
			break;
		case KeyCode::F11:
			m_Data.m_Fullscreen = !m_Data.m_Fullscreen;
			m_Data.m_Window->SetFullscreen(m_Data.m_Fullscreen);
			break;
		}
		return false;
	}
}