
#include "Common.h"

#include "Renderer/Renderer/VertexBuffer.h"
#include "Renderer/Renderer/Renderer.h"
#include "Log/Log.h"
#include "Profiler/Profiler.h"


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
			bool m_bInitialized = false;
		};

		// --------------------------------------------------------------------------------
		VertexBuffer::VertexBufferImpl::VertexBufferImpl()
		{
		}

		// --------------------------------------------------------------------------------
		VertexBuffer::VertexBuffer()
			: m_pImpl{ std::make_unique<VertexBufferImpl>() }
		{
			
		}

		// --------------------------------------------------------------------------------
		VertexBuffer::VertexBuffer(uint32_t vertexCount, uint8_t vertexStride)
			: m_pImpl{ std::make_unique<VertexBufferImpl>() }
		{
			Create(vertexCount, vertexStride);
		}

		// --------------------------------------------------------------------------------
		VertexBuffer::~VertexBuffer()
		{
			if (m_pImpl->m_bInitialized)
			{
				glCallAndCheck(glDeleteBuffers, 1, &m_pImpl->m_vbId);
				glCallAndCheck(glDeleteVertexArrays,1, &m_pImpl->m_vaoId);
			}
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::Create(uint32_t vertexCount, uint8_t vertexStride)
		{
			if (!m_pImpl->m_bInitialized)
			{
				glCallAndCheck(glGenVertexArrays, 1, &m_pImpl->m_vaoId);
				glCallAndCheck(glBindVertexArray, m_pImpl->m_vaoId);
				glCallAndCheck(glGenBuffers, 1, &m_pImpl->m_vbId);
				glCallAndCheck(glBindBuffer, GL_ARRAY_BUFFER, m_pImpl->m_vbId);
			}

			m_count = vertexCount;
			m_stride = vertexStride;
			glCallAndCheck(glBufferData, GL_ARRAY_BUFFER, vertexCount * vertexStride, nullptr, GL_STATIC_DRAW);
			m_pImpl->m_bInitialized = true;
		}
		
		// --------------------------------------------------------------------------------
		void VertexBuffer::Lock(void **ppBuff, uint32_t flags)
		{
			PROFILER_FUNC_SCOPED_TIMER;
			glCallAndCheck(glBindBuffer, GL_ARRAY_BUFFER, m_pImpl->m_vbId);
			*ppBuff = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::Unlock()
		{
			PROFILER_FUNC_SCOPED_TIMER;
			glCallAndCheck(glBindBuffer, GL_ARRAY_BUFFER, m_pImpl->m_vbId);
			glCallAndCheck(glUnmapBuffer, GL_ARRAY_BUFFER);
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::Release()
		{
			PROFILER_FUNC_SCOPED_TIMER;
			if (m_pImpl->m_bInitialized)
			{
				glCallAndCheck(glDeleteBuffers, 1, &m_pImpl->m_vbId);
				glCallAndCheck(glDeleteVertexArrays, 1, &m_pImpl->m_vaoId);
				m_pImpl->m_bInitialized = false;
			}
		}

		void VertexBuffer::Use(const std::vector<VertexElementDescriptor> &vertexElementDescriptors)
		{
			PROFILER_FUNC_SCOPED_TIMER;
			if (m_pImpl->m_bInitialized)
			{
				glCallAndCheck(glBindVertexArray, m_pImpl->m_vaoId);
				int offset = 0;
				for (auto &e : vertexElementDescriptors)
				{
					switch (e.semantic)
					{
					case VertexElementDescriptor::Semantic::position:
					{
						glCallAndCheck(glEnableVertexAttribArray, 0);
						glCallAndCheck(glBindBuffer, GL_ARRAY_BUFFER, m_pImpl->m_vbId);
						glCallAndCheck(glVertexAttribPointer, 0, e.size / sizeof(float), GL_FLOAT, GL_FALSE, m_stride, (void *)offset);
					}
						break;
					case VertexElementDescriptor::Semantic::normal:
					{
						glCallAndCheck(glEnableVertexAttribArray, 1);
						glCallAndCheck(glBindBuffer, GL_ARRAY_BUFFER, m_pImpl->m_vbId);
						glCallAndCheck(glVertexAttribPointer, 1, e.size / sizeof(float), GL_FLOAT, GL_FALSE, m_stride, (void *)offset);
					}
						break;
					case VertexElementDescriptor::Semantic::tex_coord:
					{
						glCallAndCheck(glEnableVertexAttribArray, 2);
						glCallAndCheck(glBindBuffer, GL_ARRAY_BUFFER, m_pImpl->m_vbId);
						glCallAndCheck(glVertexAttribPointer, 2, e.size / sizeof(float), GL_FLOAT, GL_FALSE, m_stride, (void *)offset);
					}
						break;
					case VertexElementDescriptor::Semantic::color:
					{
						glCallAndCheck(glEnableVertexAttribArray, 3);
						glCallAndCheck(glBindBuffer, GL_ARRAY_BUFFER, m_pImpl->m_vbId);
						glCallAndCheck(glVertexAttribPointer, 3, e.size / sizeof(float), GL_FLOAT, GL_FALSE, m_stride, (void *)offset);
					}
						break;
					default:
						Log::Error("Unrecognized vertex element semantic");
						break;
					}
					offset += e.size;
				}
			}
			else
				Log::Error("Trying to use uninitialized index buffer!");
		}

	}	// namespace render
}	// namespace oakvr

