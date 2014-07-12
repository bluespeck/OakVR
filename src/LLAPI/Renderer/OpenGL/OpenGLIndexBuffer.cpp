
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
			
			GLuint m_ibId;
			bool m_bInitialized = false;
		};

		// --------------------------------------------------------------------------------
		IndexBuffer::IndexBufferImpl::IndexBufferImpl()
		{
		}

		// --------------------------------------------------------------------------------
		IndexBuffer::IndexBuffer()
			: m_pImpl{ std::make_unique<IndexBufferImpl>() }
		{
		}
		
		// --------------------------------------------------------------------------------
		IndexBuffer::IndexBuffer(uint32_t vertexCount, uint8_t vertexStride)
			: m_pImpl{ std::make_unique<IndexBufferImpl>() }
		{
			Create(vertexCount, vertexStride);
		}

		// --------------------------------------------------------------------------------
		IndexBuffer::~IndexBuffer()
		{
			glDeleteBuffers(1, &m_pImpl->m_ibId);
		}

		// --------------------------------------------------------------------------------
		void IndexBuffer::Create(uint32_t indexCount, uint8_t indexStride)
		{
			if (m_pImpl->m_bInitialized)
			{
				glDeleteBuffers(1, &m_pImpl->m_ibId);
				m_pImpl->m_bInitialized = false;
			}
			m_count = indexCount;
			m_stride = indexStride;
			glGenBuffers(1, &m_pImpl->m_ibId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pImpl->m_ibId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * indexStride, nullptr, GL_STATIC_DRAW);
			m_pImpl->m_bInitialized = true;
		}

		// --------------------------------------------------------------------------------
		void IndexBuffer::Lock(void **ppBuff, uint32_t offsetToLock, uint32_t sizeToLock, uint32_t flags)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pImpl->m_ibId);
			*ppBuff = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_WRITE);
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
			if (m_pImpl->m_bInitialized)
			{
				glDeleteBuffers(1, &m_pImpl->m_ibId);
				m_pImpl->m_bInitialized = false;
			}
		}

		void IndexBuffer::Use()
		{
			if (m_pImpl->m_bInitialized)
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pImpl->m_ibId);
			else
				Log::PrintError("Trying to use uninitialized index buffer!");
		}

	}	// namespace render
}	// namespace oakvr
