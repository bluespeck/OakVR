#pragma once

#include <cstdint>

namespace oakvr
{
	namespace Core
	{
		class Buffer
		{
		public:
			Buffer();
			Buffer(uint32_t size);
			Buffer(const Buffer &buff);
			Buffer(Buffer &&buff);

			Buffer& operator=(const Buffer &buff);
			Buffer& operator=(Buffer &&buff);

			void CopyFromBuffer(Buffer &buff, uint32_t size, uint32_t srcOffset = 0, uint32_t offset = 0);

			void SetData(uint8_t *pData, uint32_t size);
			uint8_t *GetDataPtr() { return m_pData; }
			uint32_t GetSize() const { return m_size; }

			uint32_t Read(void *dest, uint32_t bytesToRead);
			uint32_t Write(void *src, uint32_t bytesToWrite);
			void RewindForRead() { m_readPos = 0; }
			void RewindForWrite() { m_writePos = 0; }
			void SeekForRead(uint32_t offset) { m_readPos = offset; }
			void SeekForWrite(uint32_t offset) { m_writePos = offset; }
			uint32_t TellForRead() const { return m_readPos; }
			uint32_t TellForWrite() const { return m_writePos; }

		protected:
			uint8_t *m_pData;
			uint32_t m_size;
			uint32_t m_readPos;
			uint32_t m_writePos;
		};
	}
}

