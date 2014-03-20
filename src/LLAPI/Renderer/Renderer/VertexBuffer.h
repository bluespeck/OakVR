#pragma once

#include "MeshElement.h"

#include <cstdint>
#include <memory>
#include <vector>



namespace oakvr
{
	namespace render
	{
		class VertexBuffer
		{
		public:

			VertexBuffer();
			VertexBuffer(uint32_t count, uint8_t stride);
			~VertexBuffer();

			uint32_t GetVertexCount() { return m_count; }
			uint8_t GetVertexStride() { return m_stride; }

			void Create( uint32_t count, uint8_t stride );
			void Lock( void **ppBuff, uint32_t flags = 0 );
			void Unlock();
			void Release();

			void Use();
			void Use(const std::vector<oakvr::render::VertexElementDescriptor> &vertexElementDescriptors);

		private:
			class VertexBufferImpl;
			std::unique_ptr<VertexBufferImpl> m_pImpl;

			uint32_t m_count;
			uint8_t m_stride;
		};


	}	// namespace render
}	// namespace oakvr
