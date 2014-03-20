#pragma once

#include <memory>
#include <cstdint>

namespace oakvr
{
	namespace render
	{
		class IndexBuffer
		{
		public:
			IndexBuffer();
			IndexBuffer(uint32_t count, uint8_t stride);
			~IndexBuffer();

			uint32_t GetIndexCount() { return m_count; }
			uint8_t GetIndexStride() { return m_stride; }

			void Create(uint32_t count, uint8_t stride);
			void Lock( void **ppBuff, uint32_t offsetToLock = 0, uint32_t sizeToLock = 0, uint32_t flags = 0 );
			void Unlock();
			void Release();

			void Use();
		private:
			class IndexBufferImpl;
			std::unique_ptr<IndexBufferImpl> m_pImpl;

			uint32_t m_count;
			uint8_t m_stride;
			
		};



	}	// namespace render
}	// namespace oakvr
