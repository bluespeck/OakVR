
#include "VertexBuffer.h"
#include "Engine.h"
#include "GraphicsEngine.h"

namespace Oak3D
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		VertexBuffer::VertexBuffer()
		: m_count(0)
		, m_pData(nullptr)
		, m_format(0)
		, m_vertexSize(0)
		{
		}

		// --------------------------------------------------------------------------------
		VertexBuffer::~VertexBuffer()
		{
			if(m_pData)
				Release();
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::Create(uint32_t count, uint32_t vertexFormat)
		{
			m_count = count;
			m_format = vertexFormat;
			Engine::GetGraphicsEngine()->CreateVertexBuffer(this);
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::Lock(uint32_t offsetToLock, uint32_t sizeToLock, void **ppBuff, uint32_t flags)
		{
			Engine::GetGraphicsEngine()->LockVertexBuffer(this, offsetToLock, sizeToLock, ppBuff, flags);
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::Unlock()
		{
			Engine::GetGraphicsEngine()->UnlockVertexBuffer(this);
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::Release()
		{
			Engine::GetGraphicsEngine()->ReleaseVertexBuffer(this);
		}
	}	// namespace Core
}	// namespace Oak3D