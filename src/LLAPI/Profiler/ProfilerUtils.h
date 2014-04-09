#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <cstdint>
#include <limits>

namespace oakvr
{
	namespace profiler
	{
		struct ProfileId
		{
			std::string name; // id with which to identify this profiling data
			std::string groupName; // group name in which this data is categorized
			std::string funcName; // function name in which from which the data is gathered
			std::string location; // location inside of code (file name + line number)
		};

		struct ProfilingData
		{
			ProfileId id;
			size_t hits = 0; // number of times the piece of code corresponding to this data was executed
			uint64_t minTime = -1; //[탎]
			uint64_t maxTime = 0; //[탎]
			uint64_t avgTime = 0; //[탎]
			uint64_t totalTime = 0; //[탎]
		};
	}
} // namespace oakvr