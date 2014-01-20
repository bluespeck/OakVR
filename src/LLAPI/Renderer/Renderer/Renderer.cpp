#include "Renderer.h"
#include "MeshManager.h"
#include "Mesh.h"
#include "MeshElement.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace oakvr
{
	namespace render
	{
		
		void Renderer::RegisterMesh(std::shared_ptr<Mesh> pMesh)
		{
			m_pMeshManager->AddMesh(pMesh);
		}

		// --------------------------------------------------------------------------------
		void Renderer::Update(double dt)
		{
			BeginDraw();

			for (auto &pMesh : m_pMeshManager->GetMeshes())
			{
				for (auto &pMeshElem : pMesh->GetMeshElements())
				{
					void *pBuff = nullptr;

					// Create vertex buffer for this mesh element
					VertexBuffer vb;
					unsigned long vertexCount = pMeshElem->m_vertexData.Size() / pMeshElem->m_vertexStride;
					vb.Create(vertexCount, pMeshElem->m_vertexStride);
					// and populate it with vertex data
					vb.Lock(&pBuff);
					memcpy(pBuff, pMeshElem->m_vertexData.GetDataPtr(), pMeshElem->m_vertexData.Size());
					vb.Unlock();

					
					// Create index buffer for this mesh element
					IndexBuffer ib;
					unsigned long indexCount = pMeshElem->m_indexData.Size() / pMeshElem->m_indexStride;
					ib.Create(vertexCount, pMeshElem->m_indexStride);
					// and populate it with index data
					ib.Lock(&pBuff);
					memcpy(pBuff, pMeshElem->m_indexData.GetDataPtr(), pMeshElem->m_indexData.Size());
					ib.Unlock();

					DrawIndexedPrimitives(indexCount, 0);
					
				}
			}

			EndDraw();
		}

		void Renderer::InitCommon()
		{	
			m_pMeshManager.reset(new MeshManager);
		}

	}	// namespace render
}	// namespace oakvr