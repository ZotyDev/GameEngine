#pragma once

namespace UE
{
	class Stopwatch
	{
	public:
		void Start();
		void End();

		UEUint64 ElapsedNanoseconds();
		UEUint64 ElapsedMicroseconds();
		UEUint64 ElapsedMilliseconds();
		UEUint64 ElapsedSeconds();
		
		UEFloat FormattedMilliseconds();

	private:
		std::chrono::steady_clock::time_point m_Begin;
		std::chrono::steady_clock::time_point m_End;
	};
}