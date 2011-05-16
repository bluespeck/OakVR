
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

			enum VertexFormat : uint32_t
			{
				eVF_XYZ		= 0x0001,
				eVF_Normal	= 0x0002,
				eVF_Diffuse	= 0x0004,
				eVF_Tex0	= 0x0008,	// contains tex coords pair 0
				eVF_Tex1	= 0x0010,	// contains tex coords pair 1
				eVF_Tex2	= 0x0020,	// contains tex coords pair 2
				eVF_Tex3	= 0x0040,	// contains tex coords pair 3
				eVF_Tex4	= 0x0080,	// contains tex coords pair 4
				eVF_Tex5	= 0x0100,	// contains tex coords pair 5
				eVF_Tex6	= 0x0200,	// contains tex coords pair 6
				eVF_Tex7	= 0x0400	// contains tex coords pair 7
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

			uint32_t VertexBuffer::ComputeVertexSizeFromFormat( uint32_t vertexFormat );

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
