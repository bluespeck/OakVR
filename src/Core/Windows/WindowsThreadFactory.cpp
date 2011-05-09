
#include <windows.h>
#include "WindowsThreadFactory.h"

namespace Oak3D
{
	namespace Core
	{
		void WindowsThreadFactory::CreateThread(uint32_t (pThreadFunc)(void *), void *pData)
		{
			uint32_t threadID;
			::CreateThread(NULL,						// default security attributes
				0,										// use default stack size  
				(LPTHREAD_START_ROUTINE)pThreadFunc,	// thread function name
				pData,									// argument to thread function 
				0,										// use default creation flags 
				(LPDWORD)&threadID);					// returns the thread identifier 
		}

	}	// namespace Core
}	// namespace Oak3D
