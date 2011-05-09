
#include <cstdint>

#include "Engine.h"
#include "GraphicsEngine.h"

#include "IndexBuffer.h"

using namespace std;
namespace Oak3D
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		IndexBuffer::IndexBuffer() :m_count(0), m_pData(nullptr)
		{
		}

		// --------------------------------------------------------------------------------
		IndexBuffer::~IndexBuffer()
		{
			if(m_pData)
				Release();
		}

		// --------------------------------------------------------------------------------
		void IndexBuffer::Create(uint32_t count)
		{
			m_count = count;
			Engine::GetGraphicsEngine()->CreateIndexBuffer(this);
		}

		// --------------------------------------------------------------------------------
		void IndexBuffer::Lock(uint32_t offsetToLock, uint32_t sizeToLock, void **ppBuff, uint32_t flags)
		{
			Engine::GetGraphicsEngine()->LockIndexBuffer(this, offsetToLock, sizeToLock, ppBuff, flags);
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
			m_count = 0;
		}
	}	// namespace Core
}	// namespace Oak3D
