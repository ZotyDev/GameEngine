#include "uepch.h"
#include "Time/Stopwatch.h"

namespace UE
{
	void Stopwatch::Start()
	{
		m_Begin = std::chrono::high_resolution_clock::now();
	}

	void Stopwatch::End()
	{
		m_End = std::chrono::high_resolution_clock::now();
	}

	UEUint64 Stopwatch::ElapsedNanoseconds()
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(m_End - m_Begin).count();
	}

	UEUint64 Stopwatch::ElapsedMicroseconds()
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(m_End - m_Begin).count();
	}

	UEUint64 Stopwatch::ElapsedMilliseconds()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(m_End - m_Begin).count();
	}

	UEUint64 Stopwatch::ElapsedSeconds()
	{
		return std::chrono::duration_cast<std::chrono::seconds>(m_End - m_Begin).count();
	}

	UEFloat Stopwatch::FormattedMilliseconds()
	{
		return (float)((double)ElapsedNanoseconds() / 1000000);
	}

	UEFloat Stopwatch::FormattedSeconds()
	{
		return (float)((double)ElapsedNanoseconds() / 1000000000);
	}
}