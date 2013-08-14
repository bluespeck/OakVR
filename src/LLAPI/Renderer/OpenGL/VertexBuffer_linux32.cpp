
#include "Renderer/Renderer/VertexBuffer.h"
#include "Renderer/Renderer/Renderer.h"

#include <GL/gl.h>
#include <GL/glext.h>


namespace oakvr
{
	namespace render
	{
		class VertexBuffer::VertexBufferImpl
		{
		public:
			VertexBufferImpl();

			uint32_t m_vertexFormat;
			uint32_t m_vertexSize;	// [bytes]
			uint32_t m_vertexCount;

			GLuint m_vbId;

		};

		// --------------------------------------------------------------------------------
		VertexBuffer::VertexBufferImpl::VertexBufferImpl()
		: m_vertexCount		{0}
		, m_vertexFormat	{0}
		, m_vertexSize		{0}
		{
		}

		// --------------------------------------------------------------------------------
		VertexBuffer::~VertexBuffer()
		{
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::Create(uint32_t vertexCount, uint32_t vertexFormat)
		{
			m_pImpl->m_vertexCount = vertexCount;
			m_pImpl->m_vertexFormat = vertexFormat;
			m_pImpl->m_vertexSize = ComputeVertexSizeFromFormat(m_pImpl->m_vertexFormat);
			glGenVertexArrays(1, &m_pImpl->m_vbId);
		}

		// --------------------------------------------------------------------------------
		uint32_t VertexBuffer::ComputeVertexSizeFromFormat(uint32_t vertexFormat)
		{
			uint32_t vertexSize = 0;
			if(vertexFormat & (uint32_t)VertexFormat::xyz)
			{
				vertexSize += 3 * sizeof(float);
			}
			if(vertexFormat & (uint32_t)VertexFormat::normal)
			{
				vertexSize += 3 * sizeof(float);
			}
			if(vertexFormat & (uint32_t)VertexFormat::diffuse)
			{
				vertexSize += 4 * sizeof(float);
			}
			if(vertexFormat & (uint32_t)VertexFormat::tex0)
			{
				vertexSize += 2 * sizeof(float);
			}
			if(vertexFormat & (uint32_t)VertexFormat::tex1)
			{
				vertexSize += 2 * sizeof(float);
			}
			if(vertexFormat & (uint32_t)VertexFormat::tex2)
			{
				vertexSize += 2 * sizeof(float);
			}
			if(vertexFormat & (uint32_t)VertexFormat::tex3)
			{
				vertexSize += 2 * sizeof(float);
			}
			if(vertexFormat & (uint32_t)VertexFormat::tex4)
			{
				vertexSize += 2 * sizeof(float);
			}
			if(vertexFormat & (uint32_t)VertexFormat::tex5)
			{
				vertexSize += 2 * sizeof(float);
			}
			if(vertexFormat & (uint32_t)VertexFormat::tex6)
			{
				vertexSize += 2 * sizeof(float);
			}
			if(vertexFormat & (uint32_t)VertexFormat::tex7)
			{
				vertexSize += 2 * sizeof(float);
			}

			return vertexSize;
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::Lock(void **ppBuff, uint32_t /*offsetToLock*/, uint32_t /*sizeToLock*/, uint32_t flags)
		{
			glBindVertexArray(m_pImpl->m_vbId);
			*ppBuff = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::Unlock()
		{
			glBindVertexArray(m_pImpl->m_vbId);
			glUnmapBuffer(GL_ARRAY_BUFFER);
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::Release()
		{
			glBindVertexArray(m_pImpl->m_vbId);
			glDeleteVertexArrays(1, &m_pImpl->m_vbId);
		}

		// --------------------------------------------------------------------------------
		uint32_t VertexBuffer::GetVertexCount()
		{
			return m_pImpl->m_vertexCount;
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::SetVertexCount(uint32_t vertexCount)
		{
			m_pImpl->m_vertexCount = vertexCount;
		}

		// --------------------------------------------------------------------------------
		void *VertexBuffer::GetData()
		{
			return nullptr;
		}

		// --------------------------------------------------------------------------------
		uint32_t VertexBuffer::GetVertexSize()
		{
			return m_pImpl->m_vertexSize;
		}

		// --------------------------------------------------------------------------------
		uint32_t VertexBuffer::GetVertexFormat()
		{
			return m_pImpl->m_vertexFormat;
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::SetVertexFormat(uint32_t vertexFormat)
		{
			m_pImpl->m_vertexFormat = vertexFormat;
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::SetVertexSize(uint32_t vertexSize)
		{
			m_pImpl->m_vertexSize = vertexSize;
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::SetData(void *pData)
		{
			;
		}

	}	// namespace Render
}	// namespace oakvr
