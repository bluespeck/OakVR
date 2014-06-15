#include "Renderer.h"
#include "MeshManager.h"
#include "Mesh.h"
#include "MeshElement.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Material.h"
#include "ResourceManager/ResourceManager.h"
#include "Profiler/Profiler.h"

#include <algorithm>

namespace oakvr
{
	namespace render
	{
		// --------------------------------------------------------------------------------
		void Renderer::Update(double dt)
		{
			PROFILER_FUNC_SCOPED_TIMER;
			BeginDraw();

			RenderMeshes(m_pMeshManager->GetMeshes());
			RenderMeshes(m_pMeshManager->GetOneFrameMeshes());

			EndDraw();

			m_pMeshManager->ClearOneFrameMeshes();
		}

		void Renderer::RenderMeshes(const MeshManager::MeshVector &meshes)
		{
			for (auto &pMesh : meshes)
			{
				for (auto &pMeshElem : pMesh->GetMeshElements())
				{
					void *pBuff = nullptr;

					// Create vertex buffer for this mesh element
					VertexBuffer vb(pMeshElem->m_vertexCount, pMeshElem->m_vertexStride);
					// and populate it with vertex data
					vb.Lock(&pBuff);

					memcpy(pBuff, pMeshElem->m_vertexData.GetDataPtr(), pMeshElem->m_vertexData.Size());
					vb.Unlock();


					// Create index buffer for this mesh element
					IndexBuffer ib(pMeshElem->m_indexCount, pMeshElem->m_indexStride);
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

					ib.Release();
					vb.Release();

				}
			}
		}

		// --------------------------------------------------------------------------------
		void Renderer::InitCommon()
		{	
			m_pMeshManager.reset(new MeshManager);
		}
		
		// --------------------------------------------------------------------------------
		void Renderer::SetRenderWindow(std::shared_ptr<RenderWindow> pRenderWindow)
		{
			m_pRenderWindow = pRenderWindow;
		}

		// --------------------------------------------------------------------------------
		void Renderer::SetResourceManager(std::shared_ptr<oakvr::core::ResourceManager> pRM)
		{
			m_pResourceManager = pRM;
		}

		// --------------------------------------------------------------------------------
		void Renderer::RegisterMesh(std::shared_ptr<Mesh> pMesh)
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

		std::shared_ptr<Mesh> Renderer::GetRegisteredMesh(const std::string &name)
		{
			auto &meshes = m_pMeshManager->GetMeshes();
			auto it = std::find_if(meshes.begin(), meshes.end(), [&name](oakvr::render::MeshManager::MeshVector::value_type &e) { return e->GetName() == name; });
			if (it != meshes.end())
				return *it;
			else
				return nullptr;
		}

		// --------------------------------------------------------------------------------
		void Renderer::RegisterOneFrameMesh(std::shared_ptr<Mesh> pMesh)
		{
			m_pMeshManager->AddOneFrameMesh(pMesh);
			for (const auto &pMeshElement : pMesh->GetMeshElements())
			{
				for (const auto &textureName : pMeshElement->m_vecTextures)
				{
					RegisterTexture(textureName, m_pResourceManager->GetResource(textureName));
				}
			}
		}

		// --------------------------------------------------------------------------------
		void Renderer::RegisterTexture(const std::string &textureName, std::shared_ptr<oakvr::core::MemoryBuffer> pBuff)
		{
			if (pBuff.get() == nullptr)
				return;
			if (m_textures.find(textureName) == m_textures.end())
				m_textures[textureName] = std::make_shared<Texture>(*pBuff);
		}

		void Renderer::RegisterShaderProgram(const std::string &shaderName)
		{
			if (m_shaderPrograms.find(shaderName) == m_shaderPrograms.end())
				m_shaderPrograms[shaderName] = std::make_shared<ShaderProgram>(
					shaderName,
					m_pResourceManager->GetResource(shaderName + "_vs"),
					m_pResourceManager->GetResource(shaderName + "_ps"),
					m_pResourceManager->GetResource(shaderName + "_gs"),
					m_pResourceManager->GetResource(shaderName + "_ds"),
					m_pResourceManager->GetResource(shaderName + "_hs"));
		}
	}	// namespace render
}	// namespace oakvr