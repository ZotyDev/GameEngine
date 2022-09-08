#pragma once

#include "KeyCodes.h"

namespace UE
{
	class Keyboard
	{
	public:
		Keyboard()
		{
			for (int i = 0; i < 512; i++)
			{
				m_State[i] = false;
			}
		}
		~Keyboard() = default;

		void SetState(KeyCode keyCode, bool state)
		{
			m_State[(int)keyCode] = state;
		}

		bool GetState(KeyCode keyCode)
		{
			return m_State[(int)keyCode];
		}

	private:
		bool m_State[512];
	};
}