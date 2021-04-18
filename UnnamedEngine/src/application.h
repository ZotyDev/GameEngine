#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "Core.h"

#include "Platform/Windows/WindowsWindow.h"
#include "Events/Event.h"
#include "Events/GamepadEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/WindowEvent.h"

#include "Logger/Logger.h"

namespace UE
{
	class UE_API Application
	{
	public:
		Application();

		virtual ~Application();

		void Run();

		void Update();
		void Render();

	private:
		bool m_Running = true;
		bool m_Minimized = false;

	private:
		void OnEvent(Event& event);

		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);
		bool OnKeyPressed(KeyPressedEvent& event);
		bool OnKeyReleased(KeyReleasedEvent& event);
		bool OnKeyTyped(KeyTypedEvent& event);
		bool OnMousePressed(MouseButtonPressedEvent& event);
		bool OnMouseReleased(MouseButtonReleasedEvent& event);
		bool OnMouseMoved(MouseMovedEvent& event);
		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnGamepadButtonPressed(GamepadButtonPressedEvent& event);
		bool OnGamepadButtonReleased(GamepadButtonReleasedEvent& event);
	};

	Application* CreateApplication();
}