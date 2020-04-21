#pragma once

#include "ProfilerUtils.h"
#include <chrono>
#include <string>

namespace oakvr::profiler
{
	class ScopedTimer
	{
	public:
		ScopedTimer(std::string name, std::string group = "", std::string funcName = "", std::string location = "");
		~ScopedTimer();

	private:
		typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint;

		ProfileId m_id;

		TimePoint m_startingTimePoint;
	};
}