
#include "Common.h"

#include "Renderer/Renderer/VertexBuffer.h"
#include "Renderer/Renderer/Renderer.h"


namespace oakvr
{
	namespace render
	{
		class VertexBuffer::VertexBufferImpl
		{
		public:
			VertexBufferImpl();

			GLuint m_vbId;
		};

		// --------------------------------------------------------------------------------
		VertexBuffer::VertexBufferImpl::VertexBufferImpl()
		{
		}

		// --------------------------------------------------------------------------------
		VertexBuffer::VertexBuffer()
			: m_pImpl{ new VertexBufferImpl() }
		{

		}
		// --------------------------------------------------------------------------------
		VertexBuffer::~VertexBuffer()
		{
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::Create(uint32_t vertexCount, uint8_t stride)
		{
			m_count = vertexCount;
			m_stride = stride;
			glGenBuffers(1, &m_pImpl->m_vbId);
		}
		/*
		// --------------------------------------------------------------------------------
		uint32_t VertexBuffer::ComputeVertexSizeFromFormat(uint32_t vertexFormat)
		{
			uint32_t vertexSize = 0;
			if (vertexFormat & (uint32_t)VertexFormat::xyz)
			{
				vertexSize += 3 * sizeof(float);
			}
			if (vertexFormat & (uint32_t)VertexFormat::normal)
			{
				vertexSize += 3 * sizeof(float);
			}
			if (vertexFormat & (uint32_t)VertexFormat::diffuse)
			{
				vertexSize += 4 * sizeof(float);
			}
			if (vertexFormat & (uint32_t)VertexFormat::tex0)
			{
				vertexSize += 2 * sizeof(float);
			}
			if (vertexFormat & (uint32_t)VertexFormat::tex1)
			{
				vertexSize += 2 * sizeof(float);
			}
			if (vertexFormat & (uint32_t)VertexFormat::tex2)
			{
				vertexSize += 2 * sizeof(float);
			}
			if (vertexFormat & (uint32_t)VertexFormat::tex3)
			{
				vertexSize += 2 * sizeof(float);
			}
			if (vertexFormat & (uint32_t)VertexFormat::tex4)
			{
				vertexSize += 2 * sizeof(float);
			}
			if (vertexFormat & (uint32_t)VertexFormat::tex5)
			{
				vertexSize += 2 * sizeof(float);
			}
			if (vertexFormat & (uint32_t)VertexFormat::tex6)
			{
				vertexSize += 2 * sizeof(float);
			}
			if (vertexFormat & (uint32_t)VertexFormat::tex7)
			{
				vertexSize += 2 * sizeof(float);
			}

			return vertexSize;
		}
		*/
		// --------------------------------------------------------------------------------
		void VertexBuffer::Lock(void **ppBuff, uint32_t flags)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_pImpl->m_vbId);
			*ppBuff = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::Unlock()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_pImpl->m_vbId);
			glUnmapBuffer(GL_ARRAY_BUFFER);
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::Release()
		{
			glDeleteVertexArrays(1, &m_pImpl->m_vbId);
		}

		void VertexBuffer::Use()
		{
			glBindVertexArray(m_pImpl->m_vbId);
		}

	}	// namespace render
}	// namespace oakvr

