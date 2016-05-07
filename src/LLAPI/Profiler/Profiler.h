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
		typedef std::vector< std::pair<std::string, ProfilingData> > ProfilingDataVector;

		class Profiler : public Singleton<Profiler>
		{
		public:
			auto Update(const ProfileId &id, uint64_t microSeconds) -> void;
			auto PrintSortedData() -> void;
			auto GetSortedProfilingData()->ProfilingDataVector;

		private:
			GroupProfilingDataMap m_groupProfilingDataMap;
		};
	}
}

#ifndef _MSC_VER
#define __FUNCTION__ __func__
#endif

#if defined(OAKVR_PROFILER_ENABLED)

#	define INTERNAL_PROFILER_CONCAT_(a, b) a ## b
#	define INTERNAL_PROFILER_CONCAT(a, b) INTERNAL_PROFILER_CONCAT_(a, b)

#	define PROFILER_SCOPED_TIMER(name, groupname) oakvr::profiler::ScopedTimer INTERNAL_PROFILER_CONCAT(oakvrScopedTimer, __LINE__)(name, groupname, __FUNCTION__, __FILE__ + std::string(":") + std::to_string(__LINE__))
#	define PROFILER_FUNC_SCOPED_TIMER oakvr::profiler::ScopedTimer INTERNAL_PROFILER_CONCAT(oakvrScopedTimer, __LINE__)(__FUNCTION__, "FunctionsAuto", __FUNCTION__, __FILE__ + std::string(":") + std::to_string(__LINE__))
#else
#	define PROFILER_SCOPED_TIMER
#	define PROFILER_FUNC_SCOPED_TIMER
#endif
