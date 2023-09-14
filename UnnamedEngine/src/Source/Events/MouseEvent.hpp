#pragma once

#include "Events/Event.hpp"
#include "Input/MouseCodes.hpp"

namespace UE
{
    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(UEFloat x, UEFloat y)
            : m_X(x), m_Y(y)
        {}

        UEFloat GetX() const { return m_X; }
        UEFloat GetY() const { return m_Y; }

        EVENT_CLASS_TYPE(MouseMovedEvent)
        EVENT_CLASS_CATEGORY(MouseEvent | InputEvent)
    private:
        UEFloat m_X;
        UEFloat m_Y;
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(UEFloat x, UEFloat y)
            : m_X(x), m_Y(y)
        {}

        UEFloat GetX() const { return m_X; }
        UEFloat GetY() const { return m_Y; }

        EVENT_CLASS_TYPE(MouseScrolledEvent)
        EVENT_CLASS_CATEGORY(MouseEvent | InputEvent)
    private:
        UEFloat m_X;
        UEFloat m_Y;
    };

    class MouseButtonEvent : public Event
    {
    public:
        inline MouseCode GetMouseCode() const { return m_MouseCode; }

        EVENT_CLASS_CATEGORY(MouseEvent | InputEvent)
    protected:
        MouseButtonEvent(MouseCode mouseCode)
            : m_MouseCode(mouseCode)
        {}

        MouseCode m_MouseCode;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(MouseCode mouseCode)
            : MouseButtonEvent(mouseCode)
        {}

        EVENT_CLASS_TYPE(MouseButtonPressedEvent)
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(MouseCode mouseCode)
            : MouseButtonEvent(mouseCode)
        {}

        EVENT_CLASS_TYPE(MouseButtonReleasedEvent)
    };
}
