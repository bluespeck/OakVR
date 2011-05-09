#include "ThreadFactory.h"

namespace Oak3D
{
	namespace Core
	{
		void ThreadFactory::CreateThread(uint32_t (pThreadFunc)(void *), void *pData)
		{
			pThreadFunc(pData);
		}
	}	// namespace Core
}	// namespace Oak3D
