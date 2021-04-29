#pragma once

#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

namespace UE
{
	const float EaseInCubic(float x)
	{
		return x * x * x;
	}

	const float EaseOutCubic(float x)
	{
		return 1 - std::pow(1 - x, 3);
	}

	const float EaseInOutCubic(float x)
	{
		return x < 0.5 ? 4 * x * x * x : 1 - std::pow(-2 * x + 2, 3) / 2;
	}
}