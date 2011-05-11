
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_INDEXBUFFER_H__
#define __OAK3D_INCLUDE_INDEXBUFFER_H__

#include "IResource.h"

namespace Oak3D
{
	namespace Core
	{
		class IndexBuffer
		{
		public:
			IndexBuffer();
			~IndexBuffer();

			inline uint32_t GetCount();
			inline void * GetData();
			inline void SetData(void *pData);

			void Create(uint32_t count);
			void Lock(uint32_t offsetToLock, uint32_t sizeToLock, void **ppBuff, uint32_t flags);
			void Unlock();
			void Release();
		private:
			uint32_t m_count;
			void *m_pData;
		};

		// --------------------------------------------------------------------------------
		inline uint32_t IndexBuffer::GetCount()
		{
			return m_count;
		}

		// --------------------------------------------------------------------------------
		inline void * IndexBuffer::GetData()
		{
			return m_pData;
		}

		// --------------------------------------------------------------------------------		
		inline void IndexBuffer::SetData(void *pData)
		{
			m_pData = pData;
		}
	}	// namespace Core
}	// namespace Oak3D

#endif
