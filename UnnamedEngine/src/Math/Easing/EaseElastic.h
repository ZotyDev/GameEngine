#pragma once

#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

namespace UE
{
	const float EaseInElastic(float x)
	{
		const float c = (2 * M_PI) / 3;

		return x == 0
			? 0
			: x == 1
			? 1
			: std::pow(2, 10 * x - 10) * std::sin((x * 10 - 10.75) * c);
	}

	const float EaseOutElastic(float x)
	{
		const float c = (2 * M_PI) / 3;

		return x == 0
			? 0
			: x == 1
			? 1
			: std::pow(2, -10 * x) * std::sin((x * 10 - 0.75) * c) + 1;
	}

	const float EaseInOutElastic(float x)
	{
		const float c = (2 * M_PI) / 4.5;

		return x == 0
			? 0
			: x == 1
			? 1
			: x < 0.5
			? -(std::pow(2, 20 * x - 10) * std::sin((20 * x - 11.125) * c)) / 2
			: (std::pow(2, -20 * x + 10) * std::sin((20 * x - 11.125) * c)) / 2 + 1;
	}
}