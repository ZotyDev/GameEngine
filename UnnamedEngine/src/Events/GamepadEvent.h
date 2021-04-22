#pragma once

#include "Event.h"
#include "Input/GamepadCodes.h"

namespace UE
{
	class GamepadEvent : public Event
	{
	public:
		GamepadCode GetGamepadCode() const { return m_GamepadCode; };

		EVENT_CLASS_CATEGORY(EventCategoryGamepad | EventCategoryInput)
	protected:
		GamepadEvent(GamepadCode gamepadcode) : m_GamepadCode(gamepadcode)
		{
		};

		GamepadCode m_GamepadCode;
	};

	class GamepadButtonPressedEvent : public GamepadEvent
	{
	public:
		GamepadButtonPressedEvent(GamepadCode gamepadcode) : GamepadEvent(gamepadcode) {};

		EVENT_CLASS_TYPE(GamepadButtonPressed)
	};

	class GamepadButtonReleasedEvent : public GamepadEvent
	{
	public:
		GamepadButtonReleasedEvent(GamepadCode gamepadcode) : GamepadEvent(gamepadcode) {};
	
		EVENT_CLASS_TYPE(GamepadButtonReleased)
	};
}