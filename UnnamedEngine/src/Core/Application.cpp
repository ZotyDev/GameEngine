#include "uepch.h"
#include "Core/Application.h"

#include "Renderer/Renderer.h"

#include "ECS/System.h"

// Todo: implement minify or iconify function inside OnWindowResize()

#include "Script/Lune/LuneModule.h"
#include "ECS/EntityLua.h"

#include "Script/LuneExposer.h"

namespace UE
{
	Application* Application::s_Instance = nullptr;

	Ref<EntityManager> m_EntityManager;

	Application::Application()
	{
		m_TimeMeasurer.Start();

		UE_CORE_INFO("Platform is {0} endian", UE_IS_NATIVE_BIG_ENDIAN() ? "big" : "little");

		UE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = Window::Create(WindowProps("UnnamedProject"));
		m_Window->SetWindowEventCallback(UE_BIND_EVENT_FN(Application::OnWindowEvent));
		m_Window->SetInputEventCallback(UE_BIND_EVENT_FN(Application::OnInputEvent));
		m_Window->SetVSync(true);
		m_Window->SetIcon("res/icon.png");

		Renderer::Init();

		m_Lune = CreateRef<LuneStack>();

		//Game.Register(*m_Lune);

		//LuneModule Core("Core");
		//Core["Test"]
		//
		//ComponentShell Health;
		//Health.Name = "Health";
		//Health.DataList.push_back(ComponentDataShell("Points", UEType::Uint32, 32));
		//Health.DataList.push_back(ComponentDataShell("Regeneration", UEType::Uint32, 32));
		//
		//m_EntityManager = CreateRef<EntityManager>();
		//
		//Entity Player;
		//m_EntityManager->CreateEntity(Player);
		//
		//UEUint32* Changer = (UEUint32*)Health.DataList[0].Data;
		//Changer[Player] = 1000;
		//
		//Changer = (UEUint32*)Health.DataList[1].Data;
		//Changer[Player] = 10;
		//
		//Changer = (UEUint32*)Health.DataList[0].Data;
		//
		//UE_CORE_INFO("Player Health: {0}", Changer[Player]);
		//
		//Changer = (UEUint32*)Health.DataList[1].Data;
		//
		//UE_CORE_INFO("Player Regeneration: {0}", Changer[Player]);

		//UEUint32* changer = (UEUint32*)Health.DataList[0].Data;
		//changer[0] = 32;

		//UE_CORE_INFO(changer[0]);

		ExposeCoreToLune(m_Lune);

		//
		//Luna.Dump();
		//
		m_Lune->ExecuteFile("data/mods/test.lua");
		//Luna.ExecuteFile("data/core/lua/CoreFunctionality.lua");


		m_Window->IsVSync();
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

	void Application::Close()
	{
		m_Running = false;
	}

	double last = 0;
	void Application::Run()
	{
		while (m_Running)
		{
			m_TimeMeasurer.End();
			float time = m_TimeMeasurer.FormattedSeconds();
			Timestep timestep = (time - m_LastFrameTime) * m_SimulationSpeed;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				// Update layers
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(timestep);
				}
			}

			m_Window->OnUpdate();
		}
	};

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

	bool Application::OnKeyPressed(KeyPressedEvent& event)
	{
		switch (event.GetKeyCode())
		{
		case KeyCode::Escape:
			m_Running = false;
			break;
		}
		return false;
	}
}