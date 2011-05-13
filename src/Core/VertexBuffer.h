
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
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

			inline uint32_t GetVertexCount();
			inline void SetVertexCount( uint32_t vertexCount );			

			inline void * GetData();
			inline void SetData(void *pData);

			inline uint32_t GetVertexSize();
			inline void SetVertexSize( uint32_t vertexSize );

			inline uint32_t GetVertexFormat();
			inline void SetVertexFormat( uint32_t vertexFormat );
			
			void Create( uint32_t count, uint32_t vertexFormat );
			void Lock( void **ppBuff, uint32_t offsetToLock = 0, uint32_t sizeToLock = 0, uint32_t flags = 0 );
			void Unlock();
			void Release();

		private:
			uint32_t m_vertexFormat;
			uint32_t m_vertexSize;	// [bytes]
			uint32_t m_vertexCount;
			void *m_pData;	// holds the address of a vertex buffer in the graphics API (DirectX or OpenGL)
		};

		// --------------------------------------------------------------------------------
		inline uint32_t VertexBuffer::GetVertexCount()
		{
			return m_vertexCount;
		}

		// --------------------------------------------------------------------------------
		inline void VertexBuffer::SetVertexCount(uint32_t vertexCount)
		{
			m_vertexCount = vertexCount;
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
		inline uint32_t VertexBuffer::GetVertexFormat()
		{
			return m_vertexFormat;
		}

		// --------------------------------------------------------------------------------		
		inline void VertexBuffer::SetVertexFormat(uint32_t vertexFormat)
		{
			m_vertexFormat = vertexFormat;
		}

		// --------------------------------------------------------------------------------
		inline void VertexBuffer::SetVertexSize(uint32_t vertexSize)
		{
			m_vertexSize = vertexSize;
		}

		// --------------------------------------------------------------------------------		
		inline void VertexBuffer::SetData(void *pData)
		{
			m_pData = pData;
		}


	}	// namespace Core
}	// namespace Oak3D

#endif
