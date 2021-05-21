#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include "Core/Base.h"

#include "Core/Window.h"

#include "Events/Event.h"
#include "Events/GamepadEvent.h"
#include "Events/KeyEvent.h"
#include "Events/WindowEvent.h"
#include "Events/NetworkEvent.h"

#include "Timestep.h"
#include "LayerStack.h"

int main(int argc, char** argv);

namespace UE
{
	class Application
	{
	public:
		Application(const std::string& name = "UnnamedProject");
		virtual ~Application();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);

		Window& GetWindow() { return *m_Window; }

		void Close();

		static Application& Get() { return *s_Instance; }
	private:
		void Run();
	private:
		Ref<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		float m_LastFrameTime = 0.0f;
		LayerStack m_LayerStack;
	private:
		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);
		bool OnKeyPressed(KeyPressedEvent& event);
		bool OnClientConnected(ClientConnectedEvent& event);
		bool OnClientDisconnected(ClientDisconectedEvent& event);
		bool OnClientMessage(ClientMessageEvent& event);
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	Application* CreateApplication();
}