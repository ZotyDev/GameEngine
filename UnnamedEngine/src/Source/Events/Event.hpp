#pragma once

#include "Core/Base.hpp"

namespace UE
{
    enum class EventType
    {
        None = 0,

        // Application events
        ApplicationStartEvent,
        ApplicationStopEvent,
        ApplicationHaltEvent,

        // Window events   
        WindowCloseEvent,
        WindowResizeEvent,
        WindowFocusEvent,
        WindowLostFocusEvent,
        WindowMovedEvent,

        // Mouse events
        MouseMovedEvent,
        MouseScrolledEvent,
        MouseButtonPressedEvent,
        MouseButtonReleasedEvent,

        // Keyboard events
        KeyPressedEvent,
        KeyReleasedEvent,
        KeyTypedEvent,
    
        // Gamepad events
        GamepadButtonPressedEvent,
        GamepadButtonReleasedEvent,
        GamepadAxisUpdatedEvent,

        // Events triggered by a client
        ClientConnectedEvent,
        ClientDisconnectedEvent,
        ClientPacketEvent,

        // Events triggered by a server
        ServerConnectedEvent,
        ServerDisconnectedEvent,
        ServerPacketEvent,

        // Renderer events
        RendererScaleChangeEvent
    };

    enum EventCategory
    {
        None = 0,
        ApplicationEvent = BIT(0),
        WindowEvent      = BIT(1),
        InputEvent       = BIT(2),
        KeyboardEvent    = BIT(3),
        MouseEvent       = BIT(4),
        MouseButtonEvent = BIT(5),
        GamepadEvent     = BIT(6),
        NetworkEvent     = BIT(7),
        RendererEvent    = BIT(8)
    };

    #define EVENT_CLASS_TYPE(type) \
        static EventType GetStaticType() { return EventType::type; } \
        virtual EventType GetEventType() const override { return GetStaticType(); }

    #define EVENT_CLASS_CATEGORY(category) \
        virtual UEUint32 GetCategoryFlags() const override { return category; }

    class Event
    {
    public:
        virtual ~Event() = default;

        UEBool m_Handled = false;

        virtual EventType GetEventType() const = 0;
        virtual UEUint32 GetCategoryFlags() const = 0;

        UEBool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }
    };

    class EventDispatcher
    {
    public:
        EventDispatcher(Event& event)
            : m_Event(event)
        {};

        template<typename T, typename F>
        UEBool Dispatch(const F& func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.m_Handled |= func(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }
    private:
        Event& m_Event;
    };
}