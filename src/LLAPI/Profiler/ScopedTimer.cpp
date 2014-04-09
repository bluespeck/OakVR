#include "ScopedTimer.h"
#include "Profiler.h"

namespace oakvr
{
	namespace profiler
	{
		ScopedTimer::ScopedTimer(std::string name, std::string group /*= ""*/, std::string funcName /*= ""*/, std::string location /*= ""*/)
		{
			m_id.name = name;
			m_id.groupName = group;
			m_id.funcName = funcName;
			m_id.location = location;

			m_startingTimePoint = TimePoint::clock::now();
		}

		ScopedTimer::~ScopedTimer()
		{
			TimePoint endingTimePoint = TimePoint::clock::now();
			uint64_t microSeconds = std::chrono::nanoseconds(endingTimePoint - m_startingTimePoint).count() / 1000UL;
			Profiler::GetInstance().Update(m_id, microSeconds);
		}
	}
}