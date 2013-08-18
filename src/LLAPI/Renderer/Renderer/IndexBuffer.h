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
			~IndexBuffer();

			uint32_t GetIndexCount();
			void SetIndexCount( uint32_t indexCount );
			
			void * GetData();
			void SetData(void *pData);

			uint32_t GetIndexSize();
			void SetIndexSize(uint32_t size);

			void Create(uint32_t count);
			void Lock( void **ppBuff, uint32_t offsetToLock = 0, uint32_t sizeToLock = 0, uint32_t flags = 0 );
			void Unlock();
			void Release();
		private:
			class IndexBufferImpl;
			std::unique_ptr<IndexBufferImpl> m_pImpl;
		};



	}	// namespace Render
}	// namespace oakvr
