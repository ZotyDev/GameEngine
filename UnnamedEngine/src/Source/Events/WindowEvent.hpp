#pragma once

#include "Events/Event.hpp"

namespace UE
{
    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(UEUint32 width, UEUint32 height)
            : m_Width(width), m_Height(height)
        {}

        UEUint32 GetWidth()  const { return m_Width; }
        UEUint32 GetHeight() const { return m_Height; }

        EVENT_CLASS_TYPE(WindowResizeEvent)
        EVENT_CLASS_CATEGORY(WindowEvent)
    private:
        UEUint32 m_Width;
        UEUint32 m_Height;
    };

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WindowCloseEvent);
        EVENT_CLASS_CATEGORY(WindowEvent);
    };

    class WindowFocusEvent : public Event
    {
    public:
        WindowFocusEvent() = default;

        EVENT_CLASS_TYPE(WindowFocusEvent);
        EVENT_CLASS_CATEGORY(WindowEvent);
    };

    class WindowLostFocusEvent : public Event
    {
    public:
        WindowLostFocusEvent() = default;

        EVENT_CLASS_TYPE(WindowLostFocusEvent);
        EVENT_CLASS_CATEGORY(WindowEvent);
    };

    class WindowMovedEvent : public Event
    {
    public:
        WindowMovedEvent(UEUint32 x, UEUint32 y)
            : m_X(x), m_Y(y)
        {}

        UEUint32 GetX() const { return m_X; }
        UEUint32 GetY() const { return m_Y; }

        EVENT_CLASS_TYPE(WindowMovedEvent);
        EVENT_CLASS_CATEGORY(WindowEvent);
    private:
        UEUint32 m_X;
        UEUint32 m_Y;
    };
}
