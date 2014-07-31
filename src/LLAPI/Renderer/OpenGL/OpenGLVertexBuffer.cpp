
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
				glDeleteBuffers(1, &m_pImpl->m_vbId);
				glDeleteVertexArrays(1, &m_pImpl->m_vaoId);
			}
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::Create(uint32_t vertexCount, uint8_t vertexStride)
		{
			if (m_pImpl->m_bInitialized)
			{
				glDeleteBuffers(1, &m_pImpl->m_vbId);
				glDeleteVertexArrays(1, &m_pImpl->m_vaoId);
				m_pImpl->m_bInitialized = false;
			}

			m_count = vertexCount;
			m_stride = vertexStride;
			glGenVertexArrays(1, &m_pImpl->m_vaoId);
			glBindVertexArray(m_pImpl->m_vaoId);
			glGenBuffers(1, &m_pImpl->m_vbId);
			glBindBuffer(GL_ARRAY_BUFFER, m_pImpl->m_vbId);
			glBufferData(GL_ARRAY_BUFFER, vertexCount * vertexStride, nullptr, GL_STATIC_DRAW);
			m_pImpl->m_bInitialized = true;
		}
		
		// --------------------------------------------------------------------------------
		void VertexBuffer::Lock(void **ppBuff, uint32_t flags)
		{
			PROFILER_FUNC_SCOPED_TIMER;
			glBindBuffer(GL_ARRAY_BUFFER, m_pImpl->m_vbId);
			*ppBuff = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::Unlock()
		{
			PROFILER_FUNC_SCOPED_TIMER;
			glBindBuffer(GL_ARRAY_BUFFER, m_pImpl->m_vbId);
			glUnmapBuffer(GL_ARRAY_BUFFER);
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::Release()
		{
			PROFILER_FUNC_SCOPED_TIMER;
			if (m_pImpl->m_bInitialized)
			{
				glDeleteBuffers(1, &m_pImpl->m_vbId);
				glDeleteVertexArrays(1, &m_pImpl->m_vaoId);
				m_pImpl->m_bInitialized = false;
			}
		}

		void VertexBuffer::Use(const std::vector<VertexElementDescriptor> &vertexElementDescriptors)
		{
			PROFILER_FUNC_SCOPED_TIMER;
			if (m_pImpl->m_bInitialized)
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
						glVertexAttribPointer(0, e.size / sizeof(float), GL_FLOAT, GL_FALSE, m_stride, (void *)offset);
					}
						break;
					case VertexElementDescriptor::Semantic::normal:
					{
						glEnableVertexAttribArray(1);
						glBindBuffer(GL_ARRAY_BUFFER, m_pImpl->m_vbId);
						glVertexAttribPointer(1, e.size / sizeof(float), GL_FLOAT, GL_FALSE, m_stride, (void *)offset);
					}
						break;
					case VertexElementDescriptor::Semantic::tex_coord:
					{
						glEnableVertexAttribArray(2);
						glBindBuffer(GL_ARRAY_BUFFER, m_pImpl->m_vbId);
						glVertexAttribPointer(2, e.size / sizeof(float), GL_FLOAT, GL_FALSE, m_stride, (void *)offset);
					}
						break;
					case VertexElementDescriptor::Semantic::color:
					{
						glEnableVertexAttribArray(3);
						glBindBuffer(GL_ARRAY_BUFFER, m_pImpl->m_vbId);
						glVertexAttribPointer(3, e.size / sizeof(float), GL_FLOAT, GL_FALSE, m_stride, (void *)offset);
					}
						break;
					default:
						Log::PrintError("Unrecognized vertex element semantic");
						break;
					}
					offset += e.size;
				}
			}
			else
				Log::PrintError("Trying to use uninitialized index buffer!");
		}

	}	// namespace render
}	// namespace oakvr

