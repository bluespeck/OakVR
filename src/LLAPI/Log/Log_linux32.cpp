#include "Log.h"
#include <cstdarg>
#include <cstdio>


namespace oakvr
{
	// --------------------------------------------------------------------------------
	void Log::Print(Log::LogLevel level, const char * logMsg, ...)
	{
		if(level == LogLevel::disabled || level > s_maxLevel)
			return;

		FILE * f = nullptr;
		if(level == LogLevel::error)
		{

			if(s_errFilename == "stderr")
				f = stderr;
			else
				f = fopen(s_errFilename.c_str(), "at");
			if(!f)
				f = stderr;
		}
		else
		{

			if(s_outFilename == "stdout")
			{

				f = stdout;
			}
			else
				f = fopen(s_outFilename.c_str(), "at");
			if(!f)
				f = stdout;
		}

		switch(level)
		{
		case LogLevel::info:
			fprintf(f, (std::string(s_logLabel) + " Info: ").c_str());
			break;
		case LogLevel::warning:
			fprintf(f, (std::string(s_logLabel) + " Warning: ").c_str());
			break;
		case LogLevel::error:
			fprintf(f, (std::string(s_logLabel) + " Error: ").c_str());
			break;
		dafault:
			break;
		}

		va_list vl;
		va_start(vl, logMsg);
		fprintf(f, logMsg, vl);
		va_end(vl);
		fflush(f);
		if(f != stderr && f != stdout)
			fclose(f);

	}
}
