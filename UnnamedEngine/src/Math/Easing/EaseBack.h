#pragma once

#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

namespace UE
{
	const float EaseInBack(float x)
	{
		return 2.70158 * x * x * x - 1.70158 * x;
	}

	const float EaseOutBack(float x)
	{
		return 1 + 2.70158 * std::pow(x - 1, 3) + 1.70158 * std::pow(x - 1, 2);
	}

	const float EaseInOutBack(float x)
	{
		return x < 0.5
			? (std::pow(2 * x, 2) * (3.5949095 * 2 * -2.5949095)) / 2
			: (std::pow(2 * x - 2, 2) * (3.594095 * (x * 2 - 2) + 2.5949095) + 2) / 2;
	}
}