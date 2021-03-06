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

		static auto Error(const char * logMsg, ...) -> void;
		static auto Warning(const char * logMsg, ...) -> void;
		static auto Info(const char * logMsg, ...) -> void;


		static auto SetMaxLevel(LogLevel level) -> void;
		static auto GetMaxLevel() -> LogLevel;

		static auto SetOutFilename(std::string filename) -> void;
		static auto GetOutFilename() -> std::string;

		static auto SetErrFilename(std::string filename) -> void;
		static auto GetErrFilename() -> std::string;


		static auto Print(LogLevel level, const char * logMsg, va_list args) -> void;
	private:
		static std::string s_errFilename;
		static std::string s_outFilename;
		static LogLevel s_maxLevel;
		static const char * s_logLabel;
	};
}

#ifdef OAKVR_DEBUG
#	define OAKVR_ASSERT_MESSAGE(cond, message, ...) do{ if(!(cond)) Log::Error(message, __VA_ARGS__); }while(false)
#	define OAKVR_ASSERT(cond) do{ if(!(cond)) Log::Error(#cond); }while(false)
#else
#	define NO_OPERATION (void)0
#	define OAKVR_ASSERT_MESSAGE(cond, message, ...) NO_OPERATION
#	define OAKVR_ASSERT(cond) NO_OPERATION
#endif
