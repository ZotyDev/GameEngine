#pragma once

#include "Time/Stopwatch.h"

namespace UE
{
	class Timer
	{
	public:
		Timer(UEString name)
			: m_Name(name), m_Running(true)
		{
			m_Stopwatch.Start();
		}

		~Timer()
		{
			if (m_Running)
			{
				Stop();
			}
		}

		void Stop()
		{
			m_Stopwatch.End();
			m_Running = false;
		}

	private:
		UEString m_Name;
		UEBool m_Running;
		Stopwatch m_Stopwatch;
	};
}