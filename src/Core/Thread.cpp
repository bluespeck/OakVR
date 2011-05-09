#include "Thread.h"

namespace Oak3D
{
	namespace Core
	{
		void Thread::Create(uint32_t (pThreadFunc)(void *), void *pData)
		{
			pThreadFunc(pData);
		}
	}	// namespace Core
}	// namespace Oak3D
