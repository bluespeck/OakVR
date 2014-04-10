#include "Profiler.h"
#include "Log/Log.h"

#ifdef _WIN32
#	include "Windows.h"
#endif

namespace oakvr
{
	namespace profiler
	{
		void Profiler::Update(const ProfileId &id, uint64_t microSeconds)
		{
			auto &pd = m_profilingData[id.groupName][id.name];
			
			pd.id = id;

			pd.currTime = microSeconds;

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
			for (auto &mapElem : m_profilingData)
			{
				Log::PrintInfo("[%s]", mapElem.first.c_str());
				for (auto &elem : mapElem.second)
				{
					auto &pd = elem.second;
					Log::PrintInfo("\t%80s -- h=%-6lu crt[\u00b5s]=%-9llu avg[\u00b5s]=%-9llu -- %s", pd.id.name.c_str(), pd.hits, pd.currTime, pd.avgTime, pd.id.funcName.c_str());
				}
			}
#endif
		}
	}
}