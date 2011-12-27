
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_INDEXBUFFER_H__
#define __OAK3D_INCLUDE_INDEXBUFFER_H__

#include "Core/ResourceManager/IResource.h"

namespace Oak3D
{
	namespace Render
	{
		class IndexBuffer
		{
		public:
			IndexBuffer();
			~IndexBuffer();

			inline uint32_t GetIndexCount();
			inline void SetIndexCount( uint32_t indexCount );
			
			inline void * GetData();			
			inline void SetData(void *pData);

			inline uint32_t GetIndexSize();
			inline void SetIndexSize(uint32_t size);

			void Create(uint32_t count);
			void Lock( void **ppBuff, uint32_t offsetToLock = 0, uint32_t sizeToLock = 0, uint32_t flags = 0 );
			void Unlock();
			void Release();
		private:
			uint32_t m_indexCount;
			uint32_t m_indexSize;	// [bytes]
			void *m_pData;	// holds the address of an index buffer in the graphics API (DirectX or OpenGL)
		};

		// --------------------------------------------------------------------------------
		inline uint32_t IndexBuffer::GetIndexCount()
		{
			return m_indexCount;
		}

		// --------------------------------------------------------------------------------
		inline void IndexBuffer::SetIndexCount(uint32_t indexCount)
		{
			m_indexCount = indexCount;
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

		// --------------------------------------------------------------------------------
		inline uint32_t IndexBuffer::GetIndexSize()
		{
			return m_indexSize;
		}

		inline void IndexBuffer::SetIndexSize(uint32_t size)
		{
			m_indexSize = size;
		}


	}	// namespace Render
}	// namespace Oak3D

#endif
