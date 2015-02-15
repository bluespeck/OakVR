#include "Log.h"

#include <cstdarg>
#include <iostream>

namespace oakvr
{
	std::string Log::s_outFilename = "stdout";
	std::string Log::s_errFilename = "stderr";
	const char * Log::s_logLabel = "[oakvr]";
	// default values for the maximum loglevel allowed to print messages
#ifdef OAKVR_DEBUG
	Log::LogLevel Log::s_maxLevel = Log::LogLevel::info;
#elif defined(OAKVR_FASTDEBUG)
	Log::LogLevel Log::s_maxLevel = Log::LogLevel::error;
#elif defined(OAKVR_PROFILE)
	Log::LogLevel Log::s_maxLevel = Log::LogLevel::warning;
#elif defined(OAKVR_FINAL)
	Log::LogLevel Log::s_maxLevel = Log::LogLevel::error;
#endif

	auto Log::SetMaxLevel(Log::LogLevel level) -> void
	{
		s_maxLevel = level;
	}

	auto Log::GetMaxLevel() -> Log::LogLevel
	{
		return s_maxLevel;
	}

	auto Log::SetOutFilename(std::string filename) -> void
	{
		s_outFilename = filename;
	}

	auto Log::GetOutFilename() -> std::string
	{
		return s_outFilename;
	}

	auto Log::SetErrFilename(std::string filename) -> void
	{
		s_errFilename = filename;
	}

	auto Log::GetErrFilename() -> std::string
	{
		return s_errFilename;
	}

	auto Log::Error(const char * logMsg, ...) -> void
	{
		va_list vl;
		va_start(vl, logMsg);
		Print(LogLevel::error, logMsg, vl);
		va_end(vl);
	}

	auto Log::Warning(const char * logMsg, ...) -> void
	{
		va_list vl;
		va_start(vl, logMsg);
		Print(LogLevel::warning, logMsg, vl);
		va_end(vl);
	}

	auto Log::Info(const char * logMsg, ...) -> void
	{
		va_list vl;
		va_start(vl, logMsg);
		Print(LogLevel::info, logMsg, vl);
		va_end(vl);
	}
}
