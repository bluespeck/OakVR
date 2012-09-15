#ifndef __OAK3D_INCLUDE_CORE_LLAPI_LOG_H__
#	define __OAK3D_INCLUDE_CORE_LLAPI_LOG_H__

// Oak3D logging support
// Define OAK3D_LOG_LEVEL with one of the values bellow to control logging

#define OAK3D_LOG_DISABLED 0
#define OAK3D_LOG_ERROR 1
#define OAK3D_LOG_WARNING 2
#define OAK3D_LOG_INFO 3

#ifndef OAK3D_LOG_LEVEL
#	define OAK3D_LOG_LEVEL OAK3D_LOG_INFO
#endif


namespace Oak3D
{
	void LogWarning(const char * logMsg, ...);
	void LogInfo(const char * logMsg, ...);
	void LogError(const char * logMsg, ...);
}

#endif
