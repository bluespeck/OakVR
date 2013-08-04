
#include "VertexBuffer.h"
#include "Renderer.h"
#include "Color.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"


namespace oakvr
{
	namespace render
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
			m_pData = 0;
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::Create(uint32_t vertexCount, uint32_t vertexFormat)
		{
			m_vertexCount = vertexCount;
			m_vertexFormat = vertexFormat;
			m_vertexSize = ComputeVertexSizeFromFormat(m_vertexFormat);
			//Engine::GetRenderer()->CreateVertexBuffer(this);
		}

		// --------------------------------------------------------------------------------
		uint32_t VertexBuffer::ComputeVertexSizeFromFormat(uint32_t vertexFormat)
		{
			uint32_t vertexSize = 0;
			if(vertexFormat & (uint32_t)VertexFormat::xyz)
			{
				vertexSize += sizeof(oakvr::Math::Vector3);
			}
			if(vertexFormat & (uint32_t)VertexFormat::normal)
			{
				vertexSize += sizeof(oakvr::Math::Vector3);
			}
			if(vertexFormat & (uint32_t)VertexFormat::diffuse)
			{
				vertexSize += sizeof(oakvr::render::Color);
			}
			if(vertexFormat & (uint32_t)VertexFormat::tex0)
			{
				vertexSize += sizeof(oakvr::Math::Vector2);
			}
			if(vertexFormat & (uint32_t)VertexFormat::tex1)
			{
				vertexSize += sizeof(oakvr::Math::Vector2);
			}
			if(vertexFormat & (uint32_t)VertexFormat::tex2)
			{
				vertexSize += sizeof(oakvr::Math::Vector2);
			}
			if(vertexFormat & (uint32_t)VertexFormat::tex3)
			{
				vertexSize += sizeof(oakvr::Math::Vector2);
			}
			if(vertexFormat & (uint32_t)VertexFormat::tex4)
			{
				vertexSize += sizeof(oakvr::Math::Vector2);
			}
			if(vertexFormat & (uint32_t)VertexFormat::tex5)
			{
				vertexSize += sizeof(oakvr::Math::Vector2);
			}
			if(vertexFormat & (uint32_t)VertexFormat::tex6)
			{
				vertexSize += sizeof(oakvr::Math::Vector2);
			}
			if(vertexFormat & (uint32_t)VertexFormat::tex7)
			{
				vertexSize += sizeof(oakvr::Math::Vector2);
			}

			return vertexSize;
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::Lock(void **ppBuff, uint32_t offsetToLock, uint32_t sizeToLock, uint32_t flags)
		{
			//Engine::GetRenderer()->LockVertexBuffer(this, ppBuff, offsetToLock, sizeToLock, flags);
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::Unlock()
		{
			//Engine::GetRenderer()->UnlockVertexBuffer(this);
		}

		// --------------------------------------------------------------------------------
		void VertexBuffer::Release()
		{
			//Engine::GetRenderer()->ReleaseVertexBuffer(this);
			m_pData = nullptr;
		}
	}	// namespace Render
}	// namespace oakvr
