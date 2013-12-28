
#include "Common.h"

#include "Renderer/Renderer/IndexBuffer.h"
#include "Renderer/Renderer/Renderer.h"


namespace oakvr
{
	namespace render
	{
		class IndexBuffer::IndexBufferImpl
		{
		public:
			IndexBufferImpl();

			uint32_t m_indexFormat;
			uint32_t m_indexSize;	// [bytes]
			uint32_t m_indexCount;

			GLuint m_ibId;

		};

		// --------------------------------------------------------------------------------
		IndexBuffer::IndexBufferImpl::IndexBufferImpl()
			: m_indexFormat{ 0 }
		, m_indexSize{ 4 }
		, m_indexCount{ 0 }
		{
		}

		// --------------------------------------------------------------------------------
		IndexBuffer::IndexBuffer()
			: m_pImpl{ new IndexBufferImpl() }
		{
		}

		// --------------------------------------------------------------------------------
		IndexBuffer::~IndexBuffer()
		{
		}

		// --------------------------------------------------------------------------------
		void IndexBuffer::Create(uint32_t indexCount)
		{
			m_pImpl->m_indexCount = indexCount;
			glGenBuffersARB(1, &m_pImpl->m_ibId);
		}

		// --------------------------------------------------------------------------------
		void IndexBuffer::Lock(void **ppBuff, uint32_t offsetToLock, uint32_t sizeToLock, uint32_t flags)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pImpl->m_ibId);
			*ppBuff = glMapBufferARB(GL_ELEMENT_ARRAY_BUFFER, GL_READ_WRITE);
		}

		// --------------------------------------------------------------------------------
		void IndexBuffer::Unlock()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pImpl->m_ibId);
			glUnmapBufferARB(GL_ELEMENT_ARRAY_BUFFER);
		}

		// --------------------------------------------------------------------------------
		void IndexBuffer::Release()
		{
			glDeleteBuffers(1, &m_pImpl->m_ibId);
			m_pImpl->m_ibId = -1;
		}

		// --------------------------------------------------------------------------------
		uint32_t IndexBuffer::GetIndexCount()
		{
			return m_pImpl->m_indexCount;
		}

		// --------------------------------------------------------------------------------
		void IndexBuffer::SetIndexCount(uint32_t indexCount)
		{
			m_pImpl->m_indexCount = indexCount;
		}

		// --------------------------------------------------------------------------------
		uint32_t IndexBuffer::GetIndexSize()
		{
			return m_pImpl->m_indexSize;
		}

		// --------------------------------------------------------------------------------
		void IndexBuffer::SetIndexSize(uint32_t size)
		{
			m_pImpl->m_indexSize = size;
		}
	}	// namespace render
}	// namespace oakvr
