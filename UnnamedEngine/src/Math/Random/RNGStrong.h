#pragma once

namespace UE
{
	enum class RandomType
	{
		Pseudo = 0,
		True = 1,
	};

	class Int32RNGStrong
	{
	public:
		Int32RNGStrong(UEInt32 min, UEInt32 max, RandomType type = RandomType::Pseudo);

		void SetDistribuition(UEInt32 min, UEInt32 max);

		UEInt32 operator()() { return m_Distribuition(m_Generator); }

	private:
		std::mt19937 m_Generator;
		std::uniform_int_distribution<UEInt32> m_Distribuition;
	};

	class Int64RNGStrong
	{
	public:
		Int64RNGStrong(UEInt64 min, UEInt64 max, RandomType type = RandomType::Pseudo);

		void SetDistribuition(UEInt64 min, UEInt64 max);

		UEInt64 operator()() { return m_Distribuition(m_Generator); }

	private:
		std::mt19937_64 m_Generator;
		std::uniform_int_distribution<UEInt64> m_Distribuition;
	};

	class Uint32RNGStrong
	{
	public:
		Uint32RNGStrong(UEUint32 min, UEUint32 max, RandomType type = RandomType::Pseudo);

		void SetDistribuition(UEUint32 min, UEUint32 max);

		UEInt32 operator()() { return m_Distribuition(m_Generator); }

	private:
		std::mt19937 m_Generator;
		std::uniform_int_distribution<UEUint32> m_Distribuition;
	};

	class Uint64RNGStrong
	{
	public:
		Uint64RNGStrong(UEUint64 min, UEUint64 max, RandomType type = RandomType::Pseudo);

		void SetDistribuition(UEUint64 min, UEUint64 max);

		UEInt64 operator()() { return m_Distribuition(m_Generator); }

	private:
		std::mt19937_64 m_Generator;
		std::uniform_int_distribution<UEUint64> m_Distribuition;
	};

}