
#include <cstdint>

#include "Oak3D/Engine.h"
#include "GraphicsEngine.h"

#include "IndexBuffer.h"

using namespace std;
namespace Oak3D
{
	namespace Render
	{
		// --------------------------------------------------------------------------------
		IndexBuffer::IndexBuffer() :m_indexCount(0), m_pData(nullptr), m_indexSize(4)
		{
		}

		// --------------------------------------------------------------------------------
		IndexBuffer::~IndexBuffer()
		{
			if(m_pData)
				Release();
		}

		// --------------------------------------------------------------------------------
		void IndexBuffer::Create(uint32_t indexCount)
		{
			m_indexCount = indexCount;
			Engine::GetGraphicsEngine()->CreateIndexBuffer(this);
		}

		// --------------------------------------------------------------------------------
		void IndexBuffer::Lock(void **ppBuff, uint32_t offsetToLock, uint32_t sizeToLock, uint32_t flags)
		{
			Engine::GetGraphicsEngine()->LockIndexBuffer(this, ppBuff, offsetToLock, sizeToLock, flags);
		}

		// --------------------------------------------------------------------------------
		void IndexBuffer::Unlock()
		{
			Engine::GetGraphicsEngine()->UnlockIndexBuffer(this);
		}

		// --------------------------------------------------------------------------------
		void IndexBuffer::Release()
		{
			Engine::GetGraphicsEngine()->ReleaseIndexBuffer(this);
			m_pData = nullptr;
			m_indexCount = 0;
		}
	}	// namespace Render
}	// namespace Oak3D
