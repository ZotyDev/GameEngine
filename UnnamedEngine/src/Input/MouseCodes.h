#pragma once

namespace UE
{
	typedef enum class MouseCode : unsigned short int
	{
		B0			= 0,
		B1			= 1,
		B2			= 2,
		B3			= 3,
		B4			= 4,
		B5			= 5,
		B6			= 6,
		B7			= 7,
		
		Last		= B7,
		Left		= B0,
		Right		= B1,
		Middle		= B2
	} Mouse;
}