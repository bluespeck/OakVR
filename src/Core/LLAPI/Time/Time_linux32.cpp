#include <sys/time.h>
#include <ctime>

#include "Time.h"

namespace Oak3D
{
	// --------------------------------------------------------------------------------
	uint64_t GetTimeInMicroSeconds()
	{
		timeval tv;
		gettimeofday(&tv, nullptr);
		return (uint64_t)tv.tv_sec * 1000000 + tv.tv_usec;
	}
	
	// --------------------------------------------------------------------------------
	uint64_t GetTimeInMiliSeconds()
	{
		timeval tv;
		gettimeofday(&tv, nullptr);
		return (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}
	
	// --------------------------------------------------------------------------------
	uint64_t GetTimeInSeconds()
	{
		timeval tv;
		gettimeofday(&tv, nullptr);
		return (uint64_t)tv.tv_sec;
	}
	
	// --------------------------------------------------------------------------------
	Time GetCurrentTime()
	{
		
		struct tm tt;
		gmtime_r(nullptr, &tt);
		Time t;
		t.second = tt.tm_sec;
		t.minute = tt.tm_min;
		t.hour = tt.tm_hour;
		t.day = tt.tm_mday;
		t.month = tt.tm_mon;
		t.year = tt.tm_year;
		return t;
	}
	
	// --------------------------------------------------------------------------------
	TimeOfDay GetCurrentTimeOfDay()
	{
		struct tm tt;
		gmtime_r(nullptr, &tt);
		TimeOfDay t;
		t.second = tt.tm_sec;
		t.minute = tt.tm_min;
		t.hour = tt.tm_hour;
		return t;
	}

}


