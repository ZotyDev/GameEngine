#pragma once

#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

namespace UE
{
	const float EaseInExpo(float x)
	{
		return x == 0 ? 0 : std::pow(2, 10 * x - 10);
	}

	const float EaseOutExpo(float x)
	{
		return x == 1 ? 1 : 1 - std::pow(2, -10 * x);
	}

	const float EaseInOutExpo(float x)
	{
		return x == 0
			? 0
			: x == 1
			? 1
			: x < 0.5 ? std::pow(2, 20 * x - 10) / 2
			: (2 - std::pow(2, -20 * x + 10)) / 2;
	}
}