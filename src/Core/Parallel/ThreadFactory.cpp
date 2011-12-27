
#include "Core/Config/Oak3DConfig.h"

#if OAK3D_OS == OAK3D_OS_WINDOWS

#include <windows.h>
#include "ThreadFactory.h"
#include "Thread.h"

namespace Oak3D
{
	namespace Core
	{
		Thread *ThreadFactory::CreateThread(uint32_t (pThreadFunc)(void *), void *pData)
		{
			return new Thread(uint32_t threadID;
			::CreateThread(NULL,						// default security attributes
				0,										// use default stack size  
				(LPTHREAD_START_ROUTINE)pThreadFunc,	// thread function name
				pData,									// argument to thread function 
				0,										// use default creation flags 
				(LPDWORD)&threadID);					// returns the thread identifier 
		}

	}	// namespace Core
}	// namespace Oak3D

#endif // OAK3D_OS == OAK3D_OS_WINDOWS
