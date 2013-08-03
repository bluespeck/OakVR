#pragma once

#include <cstdint>

namespace oakvr
{
	struct Time
	{
		uint32_t year;
		uint8_t month;
		uint8_t day;
		uint8_t hour;
		uint8_t minute;
		uint8_t second;
	};

	struct TimeOfDay
	{
		uint8_t hour;
		uint8_t minute;
		uint8_t second;
	};

	uint64_t GetTimeInMicroSeconds();
	uint64_t GetTimeInMilliSeconds();
	uint64_t GetTimeInSeconds();
	
	Time GetCurrentTime();
	TimeOfDay GetCurrentTimeOfDay();
	
}
