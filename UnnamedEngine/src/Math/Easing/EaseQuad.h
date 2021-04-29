#pragma once

#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

namespace UE
{
	const float EaseInQuad(float x)
	{
		return x * x;
	}

	const float EaseOutQuad(float x)
	{
		return 1 - (1 - x) * (1 - x);
	}

	const float EaseInOutQuad(float x)
	{
		return x < 0.5 ? 2 * x * x : 1 - std::pow(-2 * x + 2, 2) / 2;
	}
}