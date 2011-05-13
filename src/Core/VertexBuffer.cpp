
#include "VertexBuffer.h"
#include "Engine.h"
#include "GraphicsEngine.h"

namespace Oak3D
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		VertexBuffer::VertexBuffer()
		: m_vertexCount(0)
		, m_pData(nullptr)
		, m_vertexFormat(0)
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
		void VertexBuffer::Create(uint32_t vertexCount, uint32_t vertexFormat)
		{
			m_vertexCount = vertexCount;
			m_vertexFormat = vertexFormat;
			Engine::GetGraphicsEngine()->CreateVertexBuffer(this);
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::Lock(void **ppBuff, uint32_t offsetToLock, uint32_t sizeToLock, uint32_t flags)
		{
			Engine::GetGraphicsEngine()->LockVertexBuffer(this, ppBuff, offsetToLock, sizeToLock, flags);
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
			m_pData = nullptr;
		}
	}	// namespace Core
}	// namespace Oak3D