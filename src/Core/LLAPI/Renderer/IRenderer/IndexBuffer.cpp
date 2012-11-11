
#include <cstdint>


#include "IRenderer.h"

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
			m_pData = 0;
		}

		// --------------------------------------------------------------------------------
		void IndexBuffer::Create(uint32_t indexCount)
		{
			m_indexCount = indexCount;
			//CreateIndexBuffer(this);
		}

		// --------------------------------------------------------------------------------
		void IndexBuffer::Lock(void **ppBuff, uint32_t offsetToLock, uint32_t sizeToLock, uint32_t flags)
		{
			//Engine::GetRenderer()->LockIndexBuffer(this, ppBuff, offsetToLock, sizeToLock, flags);
		}

		// --------------------------------------------------------------------------------
		void IndexBuffer::Unlock()
		{
			//Engine::GetRenderer()->UnlockIndexBuffer(this);
		}

		// --------------------------------------------------------------------------------
		void IndexBuffer::Release()
		{
			//Engine::GetRenderer()->ReleaseIndexBuffer(this);
			m_pData = nullptr;
			m_indexCount = 0;
		}
	}	// namespace Render
}	// namespace Oak3D
