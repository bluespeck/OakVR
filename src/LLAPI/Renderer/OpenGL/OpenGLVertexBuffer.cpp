
#include "Common.h"

#include "Renderer/Renderer/VertexBuffer.h"
#include "Renderer/Renderer/Renderer.h"
#include "Log/Log.h"


namespace oakvr
{
	namespace render
	{
		class VertexBuffer::VertexBufferImpl
		{
		public:
			VertexBufferImpl();
			GLuint m_vaoId;
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
		VertexBuffer::VertexBuffer(uint32_t vertexCount, uint8_t vertexStride)
			: m_pImpl{ new VertexBufferImpl() }
		{
			Create(vertexCount, vertexStride);
		}

		// --------------------------------------------------------------------------------
		VertexBuffer::~VertexBuffer()
		{
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::Create(uint32_t vertexCount, uint8_t vertexStride)
		{
			m_count = vertexCount;
			m_stride = vertexStride;
			glGenVertexArrays(1, &m_pImpl->m_vaoId);
			glBindVertexArray(m_pImpl->m_vaoId);
			glGenBuffers(1, &m_pImpl->m_vbId);
			glBindBuffer(GL_ARRAY_BUFFER, m_pImpl->m_vbId);
			glBufferData(GL_ARRAY_BUFFER, vertexCount * vertexStride, nullptr, GL_STATIC_DRAW);
		}
		
		// --------------------------------------------------------------------------------
		void VertexBuffer::Lock(void **ppBuff, uint32_t flags)
		{	
			glBindBuffer(GL_ARRAY_BUFFER, m_pImpl->m_vbId);
			*ppBuff = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
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
			glDeleteBuffers(1, &m_pImpl->m_vbId);
		}

		void VertexBuffer::Use(const std::vector<VertexElementDescriptor> &vertexElementDescriptors)
		{
			glBindVertexArray(m_pImpl->m_vaoId);
			int offset = 0;
			for (auto &e : vertexElementDescriptors)
			{
				switch (e.semantic)
				{
				case VertexElementDescriptor::Semantic::position:
				{
					glEnableVertexAttribArray(0);
					glBindBuffer(GL_ARRAY_BUFFER, m_pImpl->m_vbId);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, m_stride, (void *)offset);
					offset += 3 * sizeof(float);
				}
					break;
				case VertexElementDescriptor::Semantic::normal:
				{
					glEnableVertexAttribArray(1);
					glBindBuffer(GL_ARRAY_BUFFER, m_pImpl->m_vbId);
					glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, m_stride, (void *)offset);
					offset += 3 * sizeof(float);
				}
					break;
				case VertexElementDescriptor::Semantic::tex_coord:
				{
					glEnableVertexAttribArray(2);
					glBindBuffer(GL_ARRAY_BUFFER, m_pImpl->m_vbId);
					glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, m_stride, (void *)offset);
					offset += 2 * sizeof(float);
				}
					break;
				case VertexElementDescriptor::Semantic::color:
				{
					glEnableVertexAttribArray(3);
					glBindBuffer(GL_ARRAY_BUFFER, m_pImpl->m_vbId);
					glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, m_stride, (void *)offset);
					offset += 3 * sizeof(float);
				}
					break;
				default:
					Log::PrintError("Unrecognized vertex element semantic");
					break;
				}
			}
		}

	}	// namespace render
}	// namespace oakvr

