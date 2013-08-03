#include "Log.h"

namespace oakvr
{
	std::string Log::s_filename = "stdout";
	Log::LogLevel Log::s_maxLevel;

	void Log::SetMaxLevel(Log::LogLevel level)
	{
		s_maxLevel = level;
	}

	Log::LogLevel Log::GetMaxLevel()
	{
		return s_maxLevel;
	}

	void Log::SetFilename(std::string filename)
	{
		s_filename = filename;
	}

	std::string Log::GetFilename()
	{
		return s_filename;
	}
}
