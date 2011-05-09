
// --------------------------------------------------------------------------------
// Copyright      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_VERTEXBUFFER_H__
#define __OAK3D_INCLUDE_VERTEXBUFFER_H__

#include <cstdint>

namespace Oak3D
{
	namespace Core
	{
		class VertexBuffer
		{
		public:

			enum VertexFormat
			{
				eVF_XYZ		= 1,
				eVF_Normal	= 2,
				eVF_Tex0	= 4,
				eVF_Tex1	= 8,
				eVF_Diffuse	= 16
			};

			VertexBuffer();
			~VertexBuffer();

			inline uint32_t GetCount();
			inline void * GetData();
			inline uint32_t GetVertexSize();
			inline uint32_t GetFormat();

			inline void SetVertexSize(uint32_t vertexSize);
			void Create(uint32_t count, uint32_t vertexFormat);
			void Lock(uint32_t offsetToLock, uint32_t sizeToLock, void **ppBuff, uint32_t flags);
			void Unlock();
			void Release();
		private:
			uint32_t m_format;
			uint32_t m_vertexSize;
			uint32_t m_count;
			void *m_pData;
		};

		// --------------------------------------------------------------------------------
		inline uint32_t VertexBuffer::GetCount()
		{
			return m_count;
		}
		
		// --------------------------------------------------------------------------------
		inline void *VertexBuffer::GetData()
		{
			return m_pData;
		}
		
		// --------------------------------------------------------------------------------
		inline uint32_t VertexBuffer::GetVertexSize()
		{
			return m_vertexSize;
		}

		// --------------------------------------------------------------------------------
		inline uint32_t VertexBuffer::GetFormat()
		{
			return m_format;
		}

		// --------------------------------------------------------------------------------
		inline void VertexBuffer::SetVertexSize(uint32_t vertexSize)
		{
			m_vertexSize = vertexSize;
		}

	}	// namespace Core
}	// namespace Oak3D

#endif
