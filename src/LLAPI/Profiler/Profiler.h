#pragma once

#include "ProfilerUtils.h"
#include "ScopedTimer.h"
#include "Utils/Singleton.h"

#include <vector>
#include <string>

// enable this macro to have profiling data
#define OAKVR_PROFILER_ENABLED

namespace oakvr
{
	namespace profiler
	{
		typedef std::unordered_map<std::string, ProfilingData> ProfilingDataMap;
		typedef std::unordered_map<std::string, ProfilingDataMap> GroupProfilingDataMap;

		class Profiler : public Singleton<Profiler>
		{
		public:
			void Update(const ProfileId &id, uint64_t microSeconds);
			void PrintSortedData();
		private:
			GroupProfilingDataMap m_profilingData;
		};
	}
}

#ifndef _MSC_VER
#define __FUNCTION__ __func__
#endif

#define PROFILER_SCOPED_TIMER(name, groupname) oakvr::profiler::ScopedTimer oakvrScopedTimer ## __LINE__(name, groupname, __FUNCTION__, __FILE__ + std::string(":") +std::to_string(__LINE__))

#if defined(OAKVR_PROFILER_ENABLED)
#	define PROFILER_FUNC_SCOPED_TIMER oakvr::profiler::ScopedTimer oakvrScopedTimer ## __LINE__(__FUNCTION__, "FunctionsAuto", __FUNCTION__, __FILE__ + std::string(":") +std::to_string(__LINE__))
#else
#	define PROFILER_FUNC_SCOPED_TIMER
#endif
