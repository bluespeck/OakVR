#include "Log.h"
#include <cstdarg>
#include <cstdio>


namespace oakvr
{
	// --------------------------------------------------------------------------------
	void Log::Print(Log::LogLevel level, const char * logMsg, ...)
	{
		if(level != LogLevel::disabled && level > s_maxLevel)
			return;

		FILE * f = nullptr;

		if(s_filename == "stderr")
			f = stderr;
		else if(s_filename == "stdout")
			f = stdout;
		else
		{
			f = fopen(s_filename.c_str(), "at");
			if(!f)
				f = stdout;
		}

		switch(level)
		{
		case LogLevel::info:
			fprintf(f, "[oakvr] Info: ");
			break;
		case LogLevel::warning:
			fprintf(f, "[oakvr] Warning: ");
			break;
		case LogLevel::error:
			fprintf(f, "[oakvr] Error: ");
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
