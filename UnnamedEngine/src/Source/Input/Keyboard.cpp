#include "Input/Keyboard.hpp"

namespace UE
{
    void Keyboard::SetKeyState(KeyCode keyCode, UEBool isPressed)
    {
        auto it = s_KeyStates.find(keyCode);
        if (it != s_KeyStates.end())
        {
            if (isPressed)
            {
                if (it->second == KeyState::Released)
                {
                    it->second = KeyState::Pressed;
                }
                else if (it->second == KeyState::Pressed)
                {
                    it->second = KeyState::Held;
                }
            }
            else
            {
                it->second = KeyState::Released;
            }
        }
        else
        {
            if (isPressed)
            {
                s_KeyStates[keyCode] = KeyState::Pressed;
            }
            else
            {
                s_KeyStates[keyCode] = KeyState::Released;
            }
        }
    }

    Keyboard::KeyState Keyboard::GetKeyState(KeyCode keyCode)
    {
        auto it = s_KeyStates.find(keyCode);
        if (it != s_KeyStates.end())
        {
            return it->second;
        }
        return KeyState::Released;
    }
}
