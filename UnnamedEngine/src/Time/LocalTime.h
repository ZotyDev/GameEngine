#pragma once

#include "Core/Base.h"

namespace UE
{
	namespace LocalTime
	{
		extern struct tm _localTime;

		inline void Update()
		{
			time_t tempCurrentTime;
			struct tm tempLocalTime;
			time(&tempCurrentTime);
			localtime_s(&tempLocalTime, &tempCurrentTime);
			_localTime = tempLocalTime;
		};

		inline unsigned int GetSecond() { return _localTime.tm_sec; };
		inline unsigned int GetMinute() { return _localTime.tm_min; };
		inline unsigned int GetHour() { return _localTime.tm_hour; };
		inline unsigned int GetMonth() { return _localTime.tm_mon; };
		inline unsigned int GetYear() { return _localTime.tm_year + 1900; };
		inline unsigned int GetWeekDay() { return _localTime.tm_wday; };
		inline unsigned int GetMonthDay() { return _localTime.tm_mday; };
		inline unsigned int GetYearDay() { return _localTime.tm_yday; };
	}
}