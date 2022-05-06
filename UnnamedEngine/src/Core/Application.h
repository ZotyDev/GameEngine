#pragma once

#include "Core/Base.h"

#include "Core/Window.h"

#include "PlatformIndependenceLayer/FileSystem.h"

#include "Events/Event.h"
#include "Events/GamepadEvent.h"
#include "Events/KeyEvent.h"
#include "Events/WindowEvent.h"
#include "Events/RendererEvent.h"

#include "Time/Stopwatch.h"

#include "Script/Lune/LuneAPI.h"

#include "Timestep.h"
#include "LayerStack.h"

#include "ImGui/ImGuiLayer.h"

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
		//void OnNetworkEvent(Event& event);
		void OnRendererEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		Window& GetWindow() { return *m_Data->m_Window; }

		void Close();

		static Application& Get() { return *s_Instance; }
	private:
		void Run();
		bool MainLoop();
	public:
		LayerStack m_LayerStack;
		struct SharedData
		{
			Ref<Window> m_Window;
			Ref<LuneStack> m_Lune;
			ImGuiLayer* m_ImGuiLayer;
			bool m_Running = true;
			bool m_Minimized = false;
			bool m_Fullscreen = false;
			float m_LastFrameTime = 0.0f;
			Stopwatch m_TimeMeasurer;
			float m_SimulationSpeed = 1.0f;
		};

		Ref<SharedData> m_Data = CreateRef<SharedData>();
	private:
		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);
		bool OnRendererScaleChange(RendererScaleChangeEvent& event);
	private:
		bool OnKeyPressed(KeyPressedEvent& event);
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	Application* CreateApplication();
}