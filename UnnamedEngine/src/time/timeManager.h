#pragma once

#include "Core.h"
#include "Pch.h"

namespace UE
{
	namespace TimeManager
	{
		time_t currentTime;
		struct tm localTime;

		UE_API void Update()
		{
			time_t tempCurrentTime;
			struct tm tempLocalTime;
			time(&tempCurrentTime);
			localtime_s(&tempLocalTime, &tempCurrentTime);
			localTime = tempLocalTime;
		}

		UE_API unsigned int GetSecond() { return localTime.tm_sec; }
		UE_API unsigned int GetMinute() { return localTime.tm_min; }
		UE_API unsigned int GetHour() { return localTime.tm_hour; }
		UE_API unsigned int GetMonthDay() { return localTime.tm_mday; }
		UE_API unsigned int GetMonth() { return localTime.tm_mon; }
		UE_API unsigned int GetYear() { return localTime.tm_year + 1900; };
		UE_API unsigned int GetWeekDay() { return localTime.tm_wday; }
		UE_API unsigned int GetYearDay() { return localTime.tm_yday; }
	}
}