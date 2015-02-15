#pragma once

#include "Utils/RenderUtils.h"

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

			auto GetVertexCount() const -> uint32_t { 
				return m_count; }
			auto GetVertexStride() const -> uint8_t { 
				return m_stride; }
			auto SetVertexCount(uint32_t count)  -> void { 
				m_count = count; }
			auto SetVertexStride(uint8_t stride)  -> void { 
				m_stride = stride; }

			auto Create( uint32_t count, uint8_t stride ) -> void;
			auto Lock( void **ppBuff, uint32_t flags = 0 ) -> void;
			auto Unlock() -> void;
			auto Release() -> void;

			auto Use(const std::vector<VertexElementDescriptor> &vertexElementDescriptors) -> void;
			
		private:
			class VertexBufferImpl;
			std::unique_ptr<VertexBufferImpl> m_pImpl;

			uint32_t m_count = 0;
			uint8_t m_stride = 0;
		};


	}	// namespace render
}	// namespace oakvr
