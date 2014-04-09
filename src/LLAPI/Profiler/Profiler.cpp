#include "Profiler.h"
#include "Log/Log.h"

namespace oakvr
{
	namespace profiler
	{
		void Profiler::Update(const ProfileId &id, uint64_t microSeconds)
		{
			auto &pd = m_profilingData[id.groupName][id.name];
			
			pd.id = id;

			if (microSeconds > pd.maxTime)
				pd.maxTime = microSeconds;
			if (microSeconds < pd.minTime)
				pd.minTime = microSeconds;

			++pd.hits;
			pd.totalTime += microSeconds;
			pd.avgTime = pd.totalTime / pd.hits;
		}

		void Profiler::PrintSortedData()
		{
			for (auto &mapElem : m_profilingData)
			{
				Log::PrintInfo("[%s]", mapElem.first.c_str());
				for (auto &elem : mapElem.second)
				{
					auto &pd = elem.second;
					Log::PrintInfo("\t%80s -- h=%-12lu avg[us]=%-12llu -- %s", pd.id.name.c_str(), pd.hits, pd.avgTime, pd.id.funcName.c_str());
				}
			}
		}
	}
}