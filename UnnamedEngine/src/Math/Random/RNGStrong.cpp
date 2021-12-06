#include "uepch.h"
#include "Math/Random/RNGStrong.h"

namespace UE
{
	Int32RNGStrong::Int32RNGStrong(UEInt32 min, UEInt32 max, RandomType type)
	{
		switch (type)
		{
		case UE::RandomType::Pseudo:
		{
			m_Generator = std::mt19937(std::time(NULL));
			break;
		}
		case UE::RandomType::True:
		{
			std::random_device RandomDevice;
			m_Generator = std::mt19937(RandomDevice());
			break;
		}
		default:
			UE_CORE_ASSERT(false, "Invalid random type");
			break;
		}

		m_Distribuition = std::uniform_int_distribution<UEInt32>(min, max);
	}

	void Int32RNGStrong::SetDistribuition(UEInt32 min, UEInt32 max)
	{
		m_Distribuition = std::uniform_int_distribution<UEInt32>(min, max);
	}

	Int64RNGStrong::Int64RNGStrong(UEInt64 min, UEInt64 max, RandomType type)
	{
		switch (type)
		{
		case UE::RandomType::Pseudo:
		{
			m_Generator = std::mt19937_64(std::time(NULL));
			break;
		}
		case UE::RandomType::True:
		{
			std::random_device RandomDevice;
			m_Generator = std::mt19937_64(RandomDevice());
			break;
		}
		default:
			UE_CORE_ASSERT(false, "Invalid random type");
			break;
		}

		m_Distribuition = std::uniform_int_distribution<UEInt64>(min, max);
	}

	void Int64RNGStrong::SetDistribuition(UEInt64 min, UEInt64 max)
	{
		m_Distribuition = std::uniform_int_distribution<UEInt64>(min, max);
	}

	Uint32RNGStrong::Uint32RNGStrong(UEUint32 min, UEUint32 max, RandomType type)
	{
		switch (type)
		{
		case UE::RandomType::Pseudo:
		{
			m_Generator = std::mt19937(std::time(NULL));
			break;
		}
		case UE::RandomType::True:
		{
			std::random_device RandomDevice;
			m_Generator = std::mt19937(RandomDevice());
			break;
		}
		default:
			UE_CORE_ASSERT(false, "Invalid random type");
			break;
		}

		m_Distribuition = std::uniform_int_distribution<UEUint32>(min, max);
	}

	void Uint32RNGStrong::SetDistribuition(UEUint32 min, UEUint32 max)
	{
		m_Distribuition = std::uniform_int_distribution<UEUint32>(min, max);
	}

	Uint64RNGStrong::Uint64RNGStrong(UEUint64 min, UEUint64 max, RandomType type)
	{
		switch (type)
		{
		case UE::RandomType::Pseudo:
		{
			m_Generator = std::mt19937_64(std::time(NULL));
			break;
		}
		case UE::RandomType::True:
		{
			std::random_device RandomDevice;
			m_Generator = std::mt19937_64(RandomDevice());
			break;
		}
		default:
			UE_CORE_ASSERT(false, "Invalid random type");
			break;
		}

		m_Distribuition = std::uniform_int_distribution<UEUint64>(min, max);
	}

	void Uint64RNGStrong::SetDistribuition(UEUint64 min, UEUint64 max)
	{
		m_Distribuition = std::uniform_int_distribution<UEUint64>(min, max);
	}
}