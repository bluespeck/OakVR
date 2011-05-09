
// --------------------------------------------------------------------------------
// Copyright      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_THREAD_H__
#define __OAK3D_INCLUDE_THREAD_H__

#include <cstdint>

namespace Oak3D
{
	namespace Core
	{
		class Thread
		{
		public:
			virtual void Create(uint32_t (pThreadFunction)(void *), void *pData);
		};
	}	// namespace Core
}	// namespace Oak3D

#endif
