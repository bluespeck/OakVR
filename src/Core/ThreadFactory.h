
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_THREADFACTORY_H__
#define __OAK3D_INCLUDE_THREADFACTORY_H__

#include <cstdint>

namespace Oak3D
{
	namespace Core
	{
		class ThreadFactory
		{
		public:
			virtual void CreateThread(uint32_t (pThreadFunction)(void *), void *pData);
		};
	}	// namespace Core
}	// namespace Oak3D

#endif
