#include <cstdarg>
#include <cstdio>
#include "Log.h"

namespace Oak3D
{
	// --------------------------------------------------------------------------------
	void LogWarning(const char * logMsg, va_list vl)
	{
#if OAK3D_LOG_LEVEL >= OAK3D_LOG_WARNING
		printf("[Oak3D] Warning: ");
		printf(logMsg, vl);
		fflush(stdout);
#endif
	}
	// --------------------------------------------------------------------------------
	void LogInfo(const char * logMsg, va_list vl)
	{
#if OAK3D_LOG_LEVEL >= OAK3D_LOG_INFO
		printf("[Oak3D] Info: ");
		printf(logMsg, vl);
		fflush(stdout);
#endif
	}
	// --------------------------------------------------------------------------------
	void LogError(const char * logMsg, va_list vl)
	{
#if OAK3D_LOG_LEVEL >= OAK3D_LOG_ERROR
		fprintf(stderr, "[Oak3D] Error: ");
		fprintf(stderr, logMsg, vl);
		fflush(stderr);
#endif
	}
}
