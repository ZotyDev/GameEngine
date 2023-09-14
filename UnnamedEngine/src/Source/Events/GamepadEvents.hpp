#pragma once

#include "Events/Event.hpp"
#include "Input/GamepadCodes.hpp"

namespace UE
{
    class GamepadButtonEvent : public Event
    {
    public:
        GamepadCode GetGamepadCode() const { return m_GamepadCode; }

        EVENT_CLASS_CATEGORY(GamepadEvent | InputEvent)
    protected:
        GamepadButtonEvent(GamepadCode gamepadCode)
            : m_GamepadCode(gamepadCode)
        {}

        GamepadCode m_GamepadCode;
    };

    class GamepadButtonPressedEvent : public GamepadButtonEvent
    {
    public:
        GamepadButtonPressedEvent(GamepadCode gamepadCode)
            : GamepadButtonEvent(gamepadCode)
        {}

        EVENT_CLASS_TYPE(GamepadButtonPressedEvent)
    };

    class GamepadButtonReleasedEvent : public GamepadButtonEvent
    {
    public:
        GamepadButtonReleasedEvent(GamepadCode gamepadCode)
            : GamepadButtonEvent(gamepadCode)
        {}

        EVENT_CLASS_TYPE(GamepadButtonReleasedEvent)
    };
}
