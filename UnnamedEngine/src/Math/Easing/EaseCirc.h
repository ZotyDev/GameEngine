#pragma once

#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

namespace UE
{
	const float EaseInCirc(float x)
	{
		return 1 - std::sqrt(1 - std::pow(x, 2));
	}

	const float EaseOutCirc(float x)
	{
		return std::sqrt(1 - std::pow(x - 1, 2));
	}

	const float EaseInOutCirc(float x)
	{
		return x < 0.5
			? (1 - std::sqrt(1 - std::pow(2 * x, 2))) / 2
			: (std::sqrt(1 - std::pow(-2 * x + 2, 2)) + 1) / 2;
	}
}