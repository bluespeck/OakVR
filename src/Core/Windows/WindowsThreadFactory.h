
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_WINDOWSTHREADFACTORY_H__
#define __OAK3D_INCLUDE_WINDOWSTHREADFACTORY_H__

#include <cstdint>
#include "../ThreadFactory.h"

namespace Oak3D
{
	namespace Core
	{
		class WindowsThreadFactory : public ThreadFactory
		{
		public:
			virtual void CreateThread(uint32_t (pThreadFunction)(void *), void *pData);
		};
	}	// namespace Core
}	// namespace Oak3D

#endif
