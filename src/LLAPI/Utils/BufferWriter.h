#pragma once

#include "Buffer.h"

#include <memory>
#include <cstdlib>

namespace oakvr
{
	namespace core
	{

		// 
		template <typename BufferUnderlyingType, typename IndexSizeType = size_t>
		class BufferWriter
		{
		public:
			// --------------------------------------------------------------------------------
			BufferWriter(Buffer<BufferUnderlyingType> &buffer) : m_rBuffer{ buffer }, m_writePos{ 0 } {}

			// --------------------------------------------------------------------------------
			template <typename T>
			auto Write(const T &data)->IndexSizeType
			{
				IndexSizeType bytesToWrite = sizeof(T);
				if (bytesToWrite + m_writePos > m_rBuffer.Size())
					return 0;
				
				memcpy(((uint8_t*)m_rBuffer.GetDataPtr()) + m_writePos, &data, bytesToWrite);
				m_writePos += bytesToWrite;
				return bytesToWrite;
			}

			template <typename OtherBufferUnderlyingType>
			auto Write(const Buffer<OtherBufferUnderlyingType> &buffer)->IndexSizeType
			{
				IndexSizeType bytesToWrite = buffer.Size();
				if (bytesToWrite + m_writePos > m_rBuffer.Size())
					return 0;
				
				memcpy(((uint8_t*)m_rBuffer.GetDataPtr()) + m_writePos, buffer.GetDataPtr(), bytesToWrite);
				m_writePos += bytesToWrite;
				return bytesToWrite;
			}

			// --------------------------------------------------------------------------------
			template <typename T>
			auto Write(T *pSrc, IndexSizeType bytesToWrite)->IndexSizeType
			{
				IndexSizeType cappedBytesToWrite;
				if (bytesToWrite + m_writePos > m_rBuffer.Size())
				{
					cappedBytesToWrite = m_rBuffer.Size() - m_writePos;
				}
				else
				{
					cappedBytesToWrite = bytesToWrite;
				}
				memcpy(((uint8_t*)m_rBuffer.GetDataPtr()) + m_writePos, pSrc, cappedBytesToWrite);
				m_writePos += cappedBytesToWrite;
				return cappedBytesToWrite;
			}

			// --------------------------------------------------------------------------------
			void Rewind()
			{
				m_writePos = 0;
			}

		private:
			Buffer<BufferUnderlyingType> &m_rBuffer;
			IndexSizeType m_writePos;
		};

		template<typename BufferType, typename IndexSizeType = size_t>
		auto MakeBufferWriter(BufferType &buffer)->BufferWriter<typename BufferType::value_type, IndexSizeType>
		{
			return BufferWriter<typename BufferType::value_type, IndexSizeType>(buffer);
		}
	}
}