#pragma once

#include <cstdint>
#include <memory>

namespace oakvr
{
	namespace render
	{
		class VertexBuffer
		{
		public:

			enum class VertexFormat : uint32_t
			{
				xyz		= 0x0001,
				normal	= 0x0002,
				diffuse	= 0x0004,
				tex0	= 0x0008,	// contains tex coords pair 0
				tex1	= 0x0010,	// contains tex coords pair 1
				tex2	= 0x0020,	// contains tex coords pair 2
				tex3	= 0x0040,	// contains tex coords pair 3
				tex4	= 0x0080,	// contains tex coords pair 4
				tex5	= 0x0100,	// contains tex coords pair 5
				tex6	= 0x0200,	// contains tex coords pair 6
				tex7	= 0x0400	// contains tex coords pair 7
			};

			VertexBuffer();
			~VertexBuffer();

			inline uint32_t GetVertexCount();
			inline void SetVertexCount( uint32_t vertexCount );			

			inline uint32_t GetVertexSize();
			inline void SetVertexSize( uint32_t vertexSize );

			inline uint32_t GetVertexFormat();
			inline void SetVertexFormat( uint32_t vertexFormat );
			
			void Create( uint32_t count, uint32_t vertexFormat );
			void Lock( void **ppBuff, uint32_t offsetToLock = 0, uint32_t sizeToLock = 0, uint32_t flags = 0 );
			void Unlock();
			void Release();

			uint32_t ComputeVertexSizeFromFormat( uint32_t vertexFormat );

		private:
			class VertexBufferImpl;
			std::unique_ptr<VertexBufferImpl> m_pImpl;

			friend class Renderer;
		};


	}	// namespace Render
}	// namespace oakvr
