#pragma once

#include "Core/Base.h"

#include "Core/Window.h"

#include "Events/Event.h"
#include "Events/GamepadEvent.h"
#include "Events/KeyEvent.h"
#include "Events/WindowEvent.h"

#include "Time/Stopwatch.h"

#include "Script/Lune/LuneAPI.h"

#include "Timestep.h"
#include "LayerStack.h"

int main(int argc, char** argv);

namespace UE
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void OnWindowEvent(Event& event);
		void OnInputEvent(Event& event);

		void PushLayer(Layer* layer);

		Window& GetWindow() { return *m_Data.m_Window; }

		void Close();

		static Application& Get() { return *s_Instance; }
	private:
		void Run();
	public:
		struct SharedData
		{
			Ref<Window> m_Window;
			Ref<UE::LuneStack> m_Lune;
			bool m_Running = true;
			bool m_Minimized = false;
			bool m_Fullscreen = false;
			float m_LastFrameTime = 0.0f;
			LayerStack m_LayerStack;
			Stopwatch m_TimeMeasurer;
			float m_SimulationSpeed = 1.0f;
		} m_Data;
	private:
		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);
	private:
		bool OnKeyPressed(KeyPressedEvent& event);
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	Application* CreateApplication();
}