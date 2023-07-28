#pragma once

#include "Events/Event.hpp"
#include "Input/KeyCodes.hpp"

namespace UE
{
    class KeyEvent : public Event
    {
    public:
        KeyCode GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(KeyboardEvent | InputEvent)
    protected:
        KeyEvent(KeyCode keyCode)
            : m_KeyCode(keyCode)
        {}

        KeyCode m_KeyCode;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(KeyCode keyCode, UEUint32 repeatCount)
            : KeyEvent(keyCode), m_RepeatCount(repeatCount)
        {}

        UEUint32 GetRepeatCount() const { return m_RepeatCount; }

        EVENT_CLASS_TYPE(KeyPressedEvent)
    private:
        UEUint32 m_RepeatCount;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(KeyCode keyCode)
            : KeyEvent(keyCode)
        {}

        EVENT_CLASS_TYPE(KeyReleasedEvent)
    };

    class KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(KeyCode keyCode)
            : KeyEvent(keyCode)
        {}

        EVENT_CLASS_TYPE(KeyTypedEvent)
    };
}