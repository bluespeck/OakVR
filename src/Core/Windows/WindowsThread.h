
// --------------------------------------------------------------------------------
// Copyright      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_WINDOWSTHREAD_H__
#define __OAK3D_INCLUDE_WINDOWSTHREAD_H__

#include <cstdint>
#include "../Thread.h"

namespace Oak3D
{
	namespace Core
	{
		class WindowsThread : public Thread
		{
		public:
			virtual void Create(uint32_t (pThreadFunction)(void *), void *pData);
		};
	}	// namespace Core
}	// namespace Oak3D

#endif
