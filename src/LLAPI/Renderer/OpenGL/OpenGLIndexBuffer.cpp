
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
			glCallAndCheck(glDeleteBuffers, 1, &m_pImpl->m_ibId);
		}

		// --------------------------------------------------------------------------------
		auto IndexBuffer::Create(uint32_t indexCount, uint8_t indexStride) -> void
		{
			if (m_pImpl->m_bInitialized)
			{
				glCallAndCheck(glDeleteBuffers, 1, &m_pImpl->m_ibId);
				m_pImpl->m_bInitialized = false;
			}
			m_count = indexCount;
			m_stride = indexStride;
			glCallAndCheck(glGenBuffers, 1, &m_pImpl->m_ibId);
			glCallAndCheck(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, m_pImpl->m_ibId);
			glCallAndCheck(glBufferData, GL_ELEMENT_ARRAY_BUFFER, indexCount * indexStride, nullptr, GL_STATIC_DRAW);
			m_pImpl->m_bInitialized = true;
		}

		// --------------------------------------------------------------------------------
		auto IndexBuffer::Lock(void **ppBuff, uint32_t offsetToLock, uint32_t sizeToLock, uint32_t flags) -> void
		{
			glCallAndCheck(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, m_pImpl->m_ibId);
			*ppBuff = glCallAndCheck(glMapBuffer, GL_ELEMENT_ARRAY_BUFFER, GL_READ_WRITE);
		}

		// --------------------------------------------------------------------------------
		auto IndexBuffer::Unlock() -> void
		{
			glCallAndCheck(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, m_pImpl->m_ibId);
			glCallAndCheck(glUnmapBufferARB, GL_ELEMENT_ARRAY_BUFFER);
		}

		// --------------------------------------------------------------------------------
		auto IndexBuffer::Release() -> void
		{
			if (m_pImpl->m_bInitialized)
			{
				glCallAndCheck(glDeleteBuffers, 1, &m_pImpl->m_ibId);
				m_pImpl->m_bInitialized = false;
			}
		}

		auto IndexBuffer::Use() -> void
		{
			if (m_pImpl->m_bInitialized)
				glCallAndCheck(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, m_pImpl->m_ibId);
			else
				Log::Error("Trying to use uninitialized index buffer!");
		}

	}	// namespace render
}	// namespace oakvr
