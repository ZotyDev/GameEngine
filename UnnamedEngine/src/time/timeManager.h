#pragma once

#include "pch.h"

namespace TimeManager
{
	time_t currentTime;
	struct tm localTime;

	void Update()
	{
		time_t tempCurrentTime;
		struct tm tempLocalTime;
		time(&tempCurrentTime);
		localtime_s(&tempLocalTime, &tempCurrentTime);
		localTime = tempLocalTime;
	}

	unsigned int GetSecond() { return localTime.tm_sec; }
	unsigned int GetMinute() { return localTime.tm_min; }
	unsigned int GetHour() { return localTime.tm_hour; }
	unsigned int GetMonthDay() { return localTime.tm_mday; }
	unsigned int GetMonth() { return localTime.tm_mon; }
	unsigned int GetYear() { return localTime.tm_year + 1900; };
	unsigned int GetWeekDay() { return localTime.tm_wday; }
	unsigned int GetYearDay() { return localTime.tm_yday; }
}