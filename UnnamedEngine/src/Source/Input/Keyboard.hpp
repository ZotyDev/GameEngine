#pragma once

#include "Core/Base.hpp"
#include "Input/KeyCodes.hpp"

namespace UE
{
    class Keyboard
    {
    public:
        enum class KeyState
        {
            Released,
            Pressed,
            Held
        };
    public:
        static void SetKeyState(KeyCode keyCode, UEBool isPressed);
        static Keyboard::KeyState GetKeyState(KeyCode keyCode);

    private:
        static std::unordered_map<KeyCode, KeyState> s_KeyStates;
    };
}
