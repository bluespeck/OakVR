#include <cstring>

#include "Buffer.h"

namespace oakvr
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		Buffer::Buffer()
			: m_pData(nullptr), m_size(0)
		{
		}

		// --------------------------------------------------------------------------------
		Buffer::Buffer(uint32_t size)
		{
			m_pData = new uint8_t[size];
			m_size = size;
		}

		// --------------------------------------------------------------------------------
		Buffer::Buffer(const Buffer &buff)
		{
			if(m_pData != nullptr)
				delete[] m_pData;

			m_size = buff.m_size;
			memcpy(m_pData, buff.m_pData, m_size);
		}

		// --------------------------------------------------------------------------------
		Buffer& Buffer::operator=(const Buffer &buff)
		{
			if(buff.m_pData != m_pData)
			{
				if(m_pData != nullptr)
					delete[] m_pData;
				m_size = buff.m_size;
				memcpy(m_pData, buff.m_pData, m_size);
			}
			return *this;
		}

		// --------------------------------------------------------------------------------
		Buffer& Buffer::operator=(Buffer &&buff)
		{
			if(buff.m_pData != m_pData)
			{	
				if(m_pData != nullptr)
					delete[] m_pData;
				m_size = buff.m_size;
				m_pData = buff.m_pData;
				buff.m_size = 0;
				buff.m_pData = nullptr;
			}
			return *this;
		}

		// --------------------------------------------------------------------------------
		Buffer::Buffer(Buffer &&buff)
		{
			if(m_pData != nullptr)
				delete[] m_pData;

			m_pData = buff.m_pData;
			buff.m_pData = nullptr;
		}

		// --------------------------------------------------------------------------------
		void Buffer::SetData(uint8_t *pData, uint32_t size)
		{
			if(m_pData != nullptr)
				delete[] m_pData;

			m_pData = new uint8_t[size];
			m_size = size;
			memcpy(m_pData, pData, m_size);
		}

		// --------------------------------------------------------------------------------
		uint32_t Buffer::Read(void *dest, uint32_t bytesToRead)
		{
			uint32_t bytesRead = (m_readPos + bytesToRead < m_size) ? bytesToRead : (m_size - m_readPos);
			
			memcpy(dest, m_pData + m_readPos, bytesRead);
			m_readPos += bytesRead;
			
			return bytesRead;
		}

		// --------------------------------------------------------------------------------
		uint32_t Buffer::Write(void *src, uint32_t bytesToWrite)
		{
			uint32_t bytesWritten = (m_writePos + bytesToWrite < m_size) ? bytesToWrite : (m_size - m_writePos);

			memcpy(m_pData + m_writePos, src, bytesWritten);
			m_writePos += bytesWritten;

			return bytesWritten;
		}

		// --------------------------------------------------------------------------------
		void Buffer::CopyFromBuffer(Buffer &buff, uint32_t size, uint32_t srcOffset, uint32_t offset)
		{
			memcpy(m_pData + offset, buff.m_pData + srcOffset, size);
		}

	}
}
