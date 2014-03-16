#include "Renderer.h"
#include "MeshManager.h"
#include "Mesh.h"
#include "MeshElement.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Material.h"


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

					vb.Use();
					ib.Use();

					auto it = m_shaders.find(pMeshElem->m_pMaterial->m_shaderName);
					if (it != std::end(m_shaders))
					{
						UseShader(it->second);
					}
					PrepareShaders();

					DrawIndexedPrimitives(indexCount, 0);

					ib.Release();
					vb.Release();
					
				}
			}

			EndDraw();
		}

		void Renderer::InitCommon()
		{	
			m_pMeshManager.reset(new MeshManager);
		}

		void Renderer::SetRenderWindow(std::shared_ptr<RenderWindow> &pRenderWindow)
		{
			m_pRenderWindow = pRenderWindow;
		}

		void Renderer::RegisterVertexShader(const std::string &shaderName, const std::shared_ptr<oakvr::core::MemoryBuffer> &buff)
		{
			if (buff.get() == nullptr)
				return;
			auto it = m_shaders.find(shaderName);
			if (it == std::end(m_shaders))
			{
				m_shaders.emplace(shaderName, std::unique_ptr<Shader>(new Shader(Shader::ShaderType::vertex, *buff)));
			}
		}

		void Renderer::RegisterPixelShader(const std::string &shaderName, const std::shared_ptr<oakvr::core::MemoryBuffer> &buff)
		{
			auto it = m_shaders.find(shaderName);
			if (it == std::end(m_shaders))
			{
				m_shaders.emplace(shaderName, std::unique_ptr<Shader>(new Shader(Shader::ShaderType::pixel, *buff)));
			}
		}

	}	// namespace render
}	// namespace oakvr