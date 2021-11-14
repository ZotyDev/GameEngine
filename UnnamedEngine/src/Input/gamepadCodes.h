#pragma once

namespace UE
{
	typedef enum class GamepadCode : unsigned short int
	{
		// Buttons
		A					= 0,
		B					= 1,
		X					= 2, 
		Y					= 3,
						
		LeftBumper			= 4,
		RightBumper			= 5,
		Back				= 6,
		Start				= 7,
		Guide				= 8,
		LeftThumb			= 9,
		RightThumb			= 10,
		DPadUp				= 11,
		DPadRight			= 12,
		DPadDown			= 13,
		DPadLeft			= 14,
						
		LastButton			= DPadLeft,

		Cross				= A,
		Circle				= B,
		Square				= X,
		Triangle			= Y,

		// Axis
		LeftX				= 0,
		LeftY				= 1,
		RightX				= 2,
		RightY				= 3,
		LeftTrigger			= 4,
		RightTrigger		= 5,

		LastAxis			= RightTrigger
	};
}