#pragma once

#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

namespace UE
{
	const float EaseInQuint(float x)
	{
		return x * x * x * x * x;
	}

	const float EaseOutQuint(float x)
	{
		return 1 - std::pow(1 - x, 5);
	}

	const float EaseInOutQuint(float x)
	{
		return x < 0.5 ? 16 * x * x * x * x * x : 1 - pow(-2 * x + 2, 5) / 2;
	}
}