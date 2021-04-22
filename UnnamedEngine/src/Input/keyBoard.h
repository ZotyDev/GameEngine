#pragma once

#include "KeyCodes.h"

namespace UE
{
	class KeyBoard
	{
	public:

		KeyBoard() = default;
		~KeyBoard() = default;

		int Initialize()
		{
			// Check if keyboard is already initialized
			if (m_Initialized)
			{
				//LOG_ERROR("Keyboard is already initialized!");
				return -1;
			}

			m_Initialized = true;
			return 0;
		}

		void SetLeftAltState(bool state) { m_LeftAltState = state; };
		void SetRightAltState(bool state) { m_RightAltState = state; };
		void SetLeftControlState(bool state) { m_LeftControlState = state; };
		void SetRightControlState(bool state) { m_RightControlState = state; };
		void SetLeftShiftState(bool state) { m_LeftShiftState = state; };
		void SetRightShiftState(bool state) { m_RightShiftState = state; };

		bool GetLeftAltState() { return m_LeftAltState; };
		bool GetRightAltState() { return m_RightAltState; };
		bool GetLeftControlState() { return m_LeftControlState; };
		bool GetRightControlState() { return m_RightControlState; };
		bool GetLeftShiftState() { return m_LeftShiftState; };
		bool GetRightShiftState() { return m_RightShiftState; };

	private:
		bool m_Initialized = false;
		bool m_LeftAltState = false;
		bool m_RightAltState = false;
		bool m_LeftControlState = false;
		bool m_RightControlState = false;
		bool m_LeftShiftState = false;
		bool m_RightShiftState = false;
	};
}