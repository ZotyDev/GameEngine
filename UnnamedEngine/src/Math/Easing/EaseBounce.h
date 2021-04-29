#pragma once

#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

namespace UE
{
	const float EaseInBounce(float x)
	{
		float y = 1 - x;

		if (y < 1 / 2.75)
		{
			return 1 - (7.5625 * y * y);
		}
		else if (y < 2 / 2.75)
		{
			return 1 - (7.5625 * (y -= 1.5 / 2.75) * y + 0.75);
		}
		else if (y < 2.5 / 2.75)
		{
			return 1 - (7.5625 * (y -= 2.25 / 2.75) * y + 0.9375);
		}
		else
		{
			return 1 - (7.5625 * (y -= 2.625 / 2.75) * y + 0.984375);
		}
	}

	const float EaseOutBounce(float x)
	{
		if (x < 1 / 2.75)
		{
			return 7.5625 * x * x;
		}
		else if (x < 2 / 2.75)
		{
			return 7.5625 * (x -= 1.5 / 2.75) * x + 0.75;
		}
		else if (x < 2.5 / 2.75)
		{
			return 7.5625 * (x -= 2.25 / 2.75) * x + 0.9375;
		}
		else
		{
			return 7.5625 * (x -= 2.625 / 2.75) * x + 0.984375;
		}
	}

	const float EaseInOutBounce(float x)
	{
		if (x < 0.5)
		{
			float y = 1 - 2 * x;
			if (y < 1 / 2.75)
			{
				return (1 - (7.5625 * y * y)) / 2;
			}
			else if (y < 2 / 2.75)
			{
				return (1 - (7.5625 * (y -= 1.5 / 2.75) * y + 0.75)) / 2;
			}
			else if (y < 2.5 / 2.75)
			{
				return (1 - (7.5625 * (y -= 2.25 / 2.75) * y + 0.9375)) / 2;
			}
			else
			{
				return (1 - (7.5625 * (y -= 2.625 / 2.75) * y + 0.984375)) / 2;
			}
		}
		else
		{
			float y = 2 * x - 1;
			if (y < 1 / 2.75)
			{
				return (1 + (7.5625 * y * y)) / 2;
			}
			else if (y < 2 / 2.75)
			{
				return (1 + (7.5625 * (y -= 1.5 / 2.75) * y + 0.75)) / 2;
			}
			else if (y < 2.5 / 2.75)
			{
				return (1 + (7.5625 * (y -= 2.25 / 2.75) * y + 0.9375)) / 2;
			}
			else
			{
				return (1 + (7.5625 * (y -= 2.625 / 2.75) * y + 0.984375)) / 2;
			}
		}
	}
}