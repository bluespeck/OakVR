#include "Renderer.h"

#include "RenderWindow.h"
#include "MeshManager.h"
#include "Mesh.h"
#include "MeshElement.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Material.h"

#include "OakVR/Camera.h"

#include "ResourceManager/ResourceManager.h"


#include "Profiler/Profiler.h"


#include "Log/Log.h"

#include <algorithm>
#include <utility>

namespace oakvr
{
	namespace render
	{
		// --------------------------------------------------------------------------------
		void Renderer::Update(double dt)
		{
			PROFILER_FUNC_SCOPED_TIMER;
			std::lock_guard<std::mutex> lockGuard(m_cleanupMutex);
			BeginDraw();

			//RenderMeshes(m_pMeshManager->GetMeshes());
			//RenderMeshes(m_pMeshManager->GetOneFrameMeshes());
			//auto sortedMeshes = m_pMeshManager->SortMeshesByMaterial();
			{
				auto sortedMeshes = m_pMeshManager->SortByCameraDistance(m_pCurrentCamera->GetPosition(), m_pCurrentCamera->GetForward());
				RenderMeshElems(sortedMeshes);
			}

			//for ()

			EndDraw();

			m_pMeshManager->ClearOneFrameMeshes();
		}

		void Renderer::RenderMeshElems(const Mesh::MeshElementVector &meshElems)
		{
			PROFILER_FUNC_SCOPED_TIMER;

			VertexBuffer vb;// (5000, 7 * sizeof(float));
			IndexBuffer ib;


			for (auto &pMeshElem : meshElems)
			{
				m_worldMatrix = pMeshElem->m_pMesh->GetWorldMatrix();
				void *pBuff = nullptr;
				if (vb.GetVertexCount() * vb.GetVertexStride() < pMeshElem->m_vertexCount * pMeshElem->m_vertexStride)
				{
					// Create vertex buffer for this mesh element
					vb.Create(pMeshElem->m_vertexCount, pMeshElem->m_vertexStride);
				}
				else if (vb.GetVertexCount() != pMeshElem->m_vertexCount || vb.GetVertexStride() != pMeshElem->m_vertexStride)
				{
					vb.SetVertexCount(pMeshElem->m_vertexCount);
					vb.SetVertexStride(pMeshElem->m_vertexStride);
				}

				// and populate it with vertex data
				vb.Lock(&pBuff);

				memcpy(pBuff, pMeshElem->m_vertexData.GetDataPtr(), pMeshElem->m_vertexData.Size());
				vb.Unlock();

				if (ib.GetIndexCount() * ib.GetIndexStride() < pMeshElem->m_indexCount * pMeshElem->m_indexStride)
				{
					// Create index buffer for this mesh element
					ib.Create(pMeshElem->m_indexCount, pMeshElem->m_indexStride);
				}

				// and populate it with index data
				ib.Lock(&pBuff);
				memcpy(pBuff, pMeshElem->m_indexData.GetDataPtr(), pMeshElem->m_indexData.Size());
				ib.Unlock();

				auto it = m_shaderPrograms.find(pMeshElem->m_pMaterial->m_shaderName);
				if (it != std::end(m_shaderPrograms))
				{
					UseShaderProgram(it->second);

					vb.Use(pMeshElem->m_vertexFormat);
					ib.Use();

					UpdateShaderParams(it->second);
					if (pMeshElem->m_vecTextures.size())
					{	
						if (m_textures[pMeshElem->m_vecTextures[0]].get())
							m_textures[pMeshElem->m_vecTextures[0]]->Use();
						else
							continue;
					}

					DrawIndexed(pMeshElem->m_indexCount);
				}
			}
			ib.Release();
			vb.Release();
		}

		void Renderer::RenderMeshes(const MeshManager::MeshVector &meshes)
		{
			PROFILER_FUNC_SCOPED_TIMER;

			VertexBuffer vb;// (5000, 7 * sizeof(float));
			IndexBuffer ib;


			for (auto &pMesh : meshes)
			{
				m_worldMatrix = pMesh->GetWorldMatrix();
				for (auto &pMeshElem : pMesh->GetMeshElements())
				{
					void *pBuff = nullptr;
					if (vb.GetVertexCount() * vb.GetVertexStride() < pMeshElem->m_vertexCount * pMeshElem->m_vertexStride)
					{
						// Create vertex buffer for this mesh element
						vb.Create(pMeshElem->m_vertexCount, pMeshElem->m_vertexStride);
					}
					// and populate it with vertex data
					vb.Lock(&pBuff);

					memcpy(pBuff, pMeshElem->m_vertexData.GetDataPtr(), pMeshElem->m_vertexData.Size());
					vb.Unlock();

					if (ib.GetIndexCount() * ib.GetIndexStride() < pMeshElem->m_indexCount * pMeshElem->m_indexStride)
					{
						// Create index buffer for this mesh element
						ib.Create(pMeshElem->m_indexCount, pMeshElem->m_indexStride);
					}

					// and populate it with index data
					ib.Lock(&pBuff);
					memcpy(pBuff, pMeshElem->m_indexData.GetDataPtr(), pMeshElem->m_indexData.Size());
					ib.Unlock();

					auto it = m_shaderPrograms.find(pMeshElem->m_pMaterial->m_shaderName);
					if (it != std::end(m_shaderPrograms))
					{
						UseShaderProgram(it->second);

						vb.Use(pMeshElem->m_vertexFormat);
						ib.Use();

						UpdateShaderParams(it->second);
						if (pMeshElem->m_vecTextures.size())
							m_textures[pMeshElem->m_vecTextures[0]]->Use();

						DrawIndexed(pMeshElem->m_indexCount);
					}
				}
			}
			ib.Release();
			vb.Release();
		}

		// --------------------------------------------------------------------------------
		void Renderer::InitCommon()
		{
			m_pMeshManager.reset(new MeshManager);
		}

		// --------------------------------------------------------------------------------
		void Renderer::Cleanup()
		{	
			std::lock_guard<std::mutex> lockGuard(m_cleanupMutex);

			if (!m_pRenderWindow->IsValid())
			{
				for (auto &e : m_shaderPrograms)
					e.second->InvalidateContext();

				for (auto &e : m_textures)
					e.second->InvalidateContext();
			}

			// force release of shader programs
			m_shaderPrograms.clear();

			// force release of textures
			m_textures.clear();
		}

		// --------------------------------------------------------------------------------
		void Renderer::SetRenderWindow(sp<RenderWindow> pRenderWindow)
		{
			m_pRenderWindow = pRenderWindow;
		}

		// --------------------------------------------------------------------------------
		void Renderer::SetResourceManager(sp<oakvr::core::ResourceManager> pRM)
		{
			m_pResourceManager = pRM;
		}

		// --------------------------------------------------------------------------------
		void Renderer::RegisterMesh(sp<Mesh> pMesh)
		{
			m_pMeshManager->AddMesh(pMesh);
			for (const auto &pMeshElement : pMesh->GetMeshElements())
			{
				for (const auto &textureName : pMeshElement->m_vecTextures)
				{
					RegisterTexture(textureName, m_pResourceManager->GetResource(textureName));
				}
			}
		}

		sp<Mesh> Renderer::GetRegisteredMesh(const StringId &name)
		{
			auto &meshes = m_pMeshManager->GetMeshes();
			auto it = std::find_if(meshes.begin(), meshes.end(), [&name](oakvr::render::MeshManager::MeshVector::value_type &e) { return e->GetName() == name; });
			if (it != meshes.end())
				return *it;
			else
				return nullptr;
		}

		// --------------------------------------------------------------------------------
		void Renderer::RegisterOneFrameMesh(sp<Mesh> pMesh)
		{
			PROFILER_FUNC_SCOPED_TIMER;
			m_pMeshManager->AddOneFrameMesh(pMesh);
			for (const auto &pMeshElement : pMesh->GetMeshElements())
			{
				for (const auto &textureName : pMeshElement->m_vecTextures)
				{
					RegisterTexture(textureName, m_pResourceManager->GetResource(textureName));
				}
			}
		}

		void Renderer::UnregisterMesh(sp<Mesh> pMesh)
		{
			m_pMeshManager->RemoveMesh(pMesh);
		}

		// --------------------------------------------------------------------------------
		void Renderer::RegisterTexture(const StringId &textureName, sp<oakvr::core::MemoryBuffer> pBuff)
		{
			PROFILER_FUNC_SCOPED_TIMER;
			if (pBuff.get() == nullptr)
				return;
			if (m_textures.find(textureName) == m_textures.end())
				m_textures[textureName] = std::make_shared<Texture>(*pBuff);
		}

		void Renderer::RegisterShaderProgram(const StringId &shaderName)
		{
			PROFILER_FUNC_SCOPED_TIMER;
			if (m_shaderPrograms.find(shaderName) == m_shaderPrograms.end())
				m_shaderPrograms[shaderName] = std::make_shared<ShaderProgram>(
				shaderName,
				m_pResourceManager->GetResource(shaderName.operator const std::string() + "_vs"),
				m_pResourceManager->GetResource(shaderName.operator const std::string() + "_ps"),
				m_pResourceManager->GetResource(shaderName.operator const std::string() + "_hs"),
				m_pResourceManager->GetResource(shaderName.operator const std::string() + "_gs"),
				m_pResourceManager->GetResource(shaderName.operator const std::string() + "_ds"));
		}
	}	// namespace render
}	// namespace oakvr