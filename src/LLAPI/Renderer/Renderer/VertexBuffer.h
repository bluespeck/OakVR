#pragma once

#include "Utils/RendererUtils.h"

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

			auto GetVertexCount() const -> uint32_t { return m_count; }
			auto GetVertexStride() const -> uint8_t { return m_stride; }
			void SetVertexCount(uint32_t count) { m_count = count; }
			void SetVertexStride(uint8_t stride) { m_stride = stride; }

			void Create( uint32_t count, uint8_t stride );
			void Lock( void **ppBuff, uint32_t flags = 0 );
			void Unlock();
			void Release();

			void VertexBuffer::Use(const std::vector<VertexElementDescriptor> &vertexElementDescriptors);
			
		private:
			class VertexBufferImpl;
			std::unique_ptr<VertexBufferImpl> m_pImpl;

			uint32_t m_count = 0;
			uint8_t m_stride = 0;
		};


	}	// namespace render
}	// namespace oakvr
