#pragma once

#include "Buffer.h"

#include <memory>
#include <cstdlib>

namespace oakvr
{
	namespace core
	{
		template <typename BufferUnderlyingType, typename IndexSizeType = size_t>
		class BufferReader
		{
		public:
			// --------------------------------------------------------------------------------
			BufferReader(const Buffer<BufferUnderlyingType> &buffer) : m_rBuffer{ buffer }, m_readPos{0} {}

			// --------------------------------------------------------------------------------
			template <typename T>
			IndexSizeType Read(T &data)
			{
				IndexSizeType bytesToRead = sizeof(T);
				if (bytesToRead + m_readPos > m_rBuffer.Size())
				{
					return 0;
				}
				memcpy(&data, ((uint8_t*)m_rBuffer.GetDataPtr()) + m_readPos, bytesToRead);
				m_readPos += bytesToRead;
				return bytesToRead;
			}

			// --------------------------------------------------------------------------------
			IndexSizeType Read(void *pDest, IndexSizeType bytesToRead)
			{
				IndexSizeType cappedBytesToRead;
				if (bytesToRead + m_readPos > m_rBuffer.Size())
				{
					cappedBytesToRead = m_rBuffer.Size() - m_readPos;
				}
				else
				{
					cappedBytesToRead = bytesToRead;
				}
				memcpy(pDest, ((uint8_t*)m_rBuffer.GetDataPtr()) + m_readPos, cappedBytesToRead);
				m_readPos += cappedBytesToRead;
				return cappedBytesToRead;
			}

			// --------------------------------------------------------------------------------
			void Rewind()
			{ 
				m_readPos = 0;
			}

		private:
			const Buffer<BufferUnderlyingType> &m_rBuffer;
			IndexSizeType m_readPos;
		};

		template<typename BufferType, typename IndexSizeType = size_t>
		BufferReader<typename BufferType::value_type, IndexSizeType> MakeBufferReader(const BufferType &buffer)
		{
			return BufferReader<typename BufferType::value_type, IndexSizeType>(buffer);
		}
	}
}