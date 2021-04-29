#pragma once

#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

namespace UE
{
	const float EaseInSine(float x)
	{
		return 1 - std::cos((x * M_PI) / 2);
	};

	const float EaseOutSine(float x)
	{
		return std::sin((x * M_PI) / 2);
	};

	const float EaseInOutSine(float x)
	{
		return -(std::cos(x * M_PI) - 1) / 2;
	};
}