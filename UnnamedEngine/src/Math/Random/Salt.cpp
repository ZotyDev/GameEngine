#include "uepch.h"
#include "Math/Random/Salt.h"

namespace UE
{
	uint64_t SaltUint64()
	{
		std::random_device RandomDevice;
		std::mt19937_64 Generator(RandomDevice());
		std::uniform_int_distribution<uint64_t> Distribuition(std::llround(std::pow(2, 62)), std::llround(std::pow(2, 63)));

		return Distribuition(Generator);
	}
}