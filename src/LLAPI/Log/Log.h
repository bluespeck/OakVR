#pragma once

#include <string>
#include <cstdint>

// oakvr logging support
// Define OAKVR_LOG_LEVEL with one of the values bellow to control logging

namespace oakvr
{
	class Log
	{
	public:
		enum class LogLevel : int8_t
		{
			disabled = 0,
			error,
			warning,
			info
		};

		static void SetMaxLevel(LogLevel level);
		static LogLevel GetMaxLevel();
		static void SetFilename(std::string filename);
		static std::string GetFilename();
		static void Print(LogLevel level, const char * logMsg, ...);
	private:
		static std::string s_filename;
		static LogLevel s_maxLevel;
	};
}
