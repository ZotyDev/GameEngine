#pragma once

#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

namespace UE
{
	const float EaseInQuart(float x)
	{
		return x * x * x * x;
	}

	const float EaseOutQuart(float x)
	{
		return 1 - std::pow(1 - x, 4);
	}

	const float EaseInOutQuart(float x)
	{
		return x < 0.5 ? 8 * x * x * x * x : 1 - std::pow(-2 * x + 2, 4) / 2;
	}
}