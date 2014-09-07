#include "Profiler.h"
#include "Log/Log.h"
#include <chrono>
#include <ratio>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>

#ifdef _WIN32
#	include "Windows.h"
#endif

namespace oakvr
{
	namespace profiler
	{
		void Profiler::Update(const ProfileId &id, uint64_t microSeconds)
		{
			auto &pd = m_groupProfilingDataMap[id.groupName][id.name];
			
			pd.id = id;

			pd.latestTime = microSeconds;

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
#if defined(OAKVR_PROFILER_ENABLED)
			PROFILER_FUNC_SCOPED_TIMER;
			static auto prevTimePoint = std::chrono::high_resolution_clock::now();
			static float accTime = 0.0f;
			auto currentTimePoint = std::chrono::high_resolution_clock::now();
			accTime += 1e-9f * std::chrono::nanoseconds(currentTimePoint - prevTimePoint).count();
			prevTimePoint = currentTimePoint;
			if (accTime < 1.f)
				return;
			else
			{
				accTime = 0.0f;
#ifdef _WIN32
				HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
				COORD coord = { 0, 0 };
				DWORD count;
				CONSOLE_SCREEN_BUFFER_INFO csbi;
				GetConsoleScreenBufferInfo(hStdOut, &csbi);
				FillConsoleOutputCharacter(hStdOut, ' ',
					csbi.dwSize.X * csbi.dwSize.Y,
					coord, &count);
				SetConsoleCursorPosition(hStdOut, coord);
#endif
				std::string oldOutFileName = Log::GetOutFilename();
				Log::SetOutFilename("stdout");

				auto vec = GetSortedProfilingData();
				
				for (auto &elem : vec)
				{
					auto &pd = elem.second;
					auto percentage = static_cast<int>(static_cast<float>(pd.totalTime) / static_cast<float>(vec.front().second.totalTime) * 100.0f);
					Log::PrintInfo("\t%60s -- [%%]=%3d h=%-6lu total[ms]=%-9llu crt[\346s]=%-9llu max[\346s]=%-9llu avg[\346s]=%-9llu", pd.id.name.c_str(), percentage, pd.hits, pd.totalTime / 1000, pd.latestTime, pd.maxTime, pd.avgTime);
				}
				Log::SetOutFilename(oldOutFileName);
			}
#endif
		}

		auto Profiler::GetSortedProfilingData()->ProfilingDataVector
		{
			ProfilingDataVector vec;

			for (auto &mapElem : m_groupProfilingDataMap)
			{
				for (auto &elem : mapElem.second)
				{
					vec.push_back(std::make_pair(const_cast<const std::string &>(elem.first), elem.second));
				}
			}

			std::sort(vec.begin(), vec.end(), [](std::pair<const std::string, oakvr::profiler::ProfilingData> p1
				, std::pair<std::string, oakvr::profiler::ProfilingData> p2)
					{ return p1.second.totalTime > p2.second.totalTime; }
			);

			return vec;
		}
	}
}