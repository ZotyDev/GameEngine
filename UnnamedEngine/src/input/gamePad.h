#pragma once

#include "core.h"
#include "gamepadCodes.h"
#include "events/gamepadEvent.h"

namespace UE
{
	class GamePad
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		int Initialize(int joystick, EventCallbackFn eventCallbackFn)
		{
			// Check if game pad is already initialized
			if (m_Initialized)
			{
				//LOG_ERROR("GamePad is already initialized!");
				return -1;
			}

			m_Joystick = joystick;
			m_EventCallbackFn = eventCallbackFn;

			m_Initialized = true;
			return 0;
		}

		~GamePad() = default;

		void Update()
		{
			m_LastState = m_State;
			glfwGetGamepadState(m_Joystick, &m_State);

			// Button event dispatcher
			for (int i = 0; i <= (int)GamepadCode::ButtonLast; i++)
			{
				if (m_LastState.buttons[i] != m_State.buttons[i])
				{
					switch (m_State.buttons[i])
					{
					case GLFW_PRESS:
					{
						GamepadButtonPressedEvent event(static_cast<GamepadCode>(i));
						m_EventCallbackFn(event);
						break;
					}
					case GLFW_RELEASE:
					{
						GamepadButtonReleasedEvent event(static_cast<GamepadCode>(i));
						m_EventCallbackFn(event);
						break;
					}
					}
				}
			}

		};

		const float GetLeftXAxisValue()
		{
			return m_State.axes[static_cast<int>(GamepadCode::AxisLeftX)];
		};

		const float GetRightXAxisValue()
		{
			return m_State.axes[static_cast<int>(GamepadCode::AxisRightX)];
		};

		const float GetLeftYAxisValue()
		{
			return m_State.axes[static_cast<int>(GamepadCode::AxisLeftY)];
		};

		const float GetRightYAxisValue()
		{
			return m_State.axes[static_cast<int>(GamepadCode::AxisRightY)];
		};

		const float GetLeftTriggerValue()
		{
			return m_State.axes[static_cast<int>(GamepadCode::AxisLeftTrigger)];
		};

		const float GetRightTriggerValue()
		{
			return m_State.axes[static_cast<int>(GamepadCode::AxisRightTrigger)];
		};

	private:
		bool m_Initialized = false;
		GLFWgamepadstate m_State;
		GLFWgamepadstate m_LastState;
		EventCallbackFn m_EventCallbackFn;
		int m_Joystick;
	};
}