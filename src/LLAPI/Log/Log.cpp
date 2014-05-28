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
	Log::LogLevel Log::s_maxLevel = Log::LogLevel::disabled;
#endif

	void Log::SetMaxLevel(Log::LogLevel level)
	{
		s_maxLevel = level;
	}

	Log::LogLevel Log::GetMaxLevel()
	{
		return s_maxLevel;
	}

	void Log::SetOutFilename(std::string filename)
	{
		s_outFilename = filename;
	}

	std::string Log::GetOutFilename()
	{
		return s_outFilename;
	}

	void Log::SetErrFilename(std::string filename)
	{
		s_errFilename = filename;
	}

	std::string Log::GetErrFilename()
	{
		return s_errFilename;
	}

	void Log::PrintError(const char * logMsg, ...)
	{
		va_list vl;
		va_start(vl, logMsg);
		Print(LogLevel::error, logMsg, vl);
		va_end(vl);
	}

	void Log::PrintWarning(const char * logMsg, ...)
	{
		va_list vl;
		va_start(vl, logMsg);
		Print(LogLevel::warning, logMsg, vl);
		va_end(vl);
	}

	void Log::PrintInfo(const char * logMsg, ...)
	{
		va_list vl;
		va_start(vl, logMsg);
		Print(LogLevel::info, logMsg, vl);
		va_end(vl);
	}
}
