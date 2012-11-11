#include <cstdarg>
#include <cstdio>
#include "Log.h"

namespace ro3d
{
	// --------------------------------------------------------------------------------
	void LogWarning(const char * logMsg, va_list vl)
	{
#if OAK3D_LOG_LEVEL >= OAK3D_LOG_WARNING
		printf("[ro3d] Warning: ");
		printf(logMsg, vl);
		fflush(stdout);
#endif
	}
	// --------------------------------------------------------------------------------
	void LogInfo(const char * logMsg, va_list vl)
	{
#if OAK3D_LOG_LEVEL >= OAK3D_LOG_INFO
		printf("[ro3d] Info: ");
		printf(logMsg, vl);
		fflush(stdout);
#endif
	}
	// --------------------------------------------------------------------------------
	void LogError(const char * logMsg, va_list vl)
	{
#if OAK3D_LOG_LEVEL >= OAK3D_LOG_ERROR
		fprintf(stderr, "[ro3d] Error: ");
		fprintf(stderr, logMsg, vl);
		fflush(stderr);
#endif
	}
}
