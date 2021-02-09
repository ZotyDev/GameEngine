#pragma once

#include "core.h"

namespace UE
{
	namespace LocalTime
	{
		extern struct tm _localTime;

		UE_API inline void Update()
		{
			time_t tempCurrentTime;
			struct tm tempLocalTime;
			time(&tempCurrentTime);
			localtime_s(&tempLocalTime, &tempCurrentTime);
			_localTime = tempLocalTime;
		};

		UE_API inline unsigned int GetSecond() { return _localTime.tm_sec; };
		UE_API inline unsigned int GetMinute() { return _localTime.tm_min; };
		UE_API inline unsigned int GetHour() { return _localTime.tm_hour; };
		UE_API inline unsigned int GetMonth() { return _localTime.tm_mon; };
		UE_API inline unsigned int GetYear() { return _localTime.tm_year + 1900; };
		UE_API inline unsigned int GetWeekDay() { return _localTime.tm_wday; };
		UE_API inline unsigned int GetMonthDay() { return _localTime.tm_mday; };
		UE_API inline unsigned int GetYearDay() { return _localTime.tm_yday; };
	}
}