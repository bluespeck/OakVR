#include "Renderer.h"
#include "MeshManager.h"
#include "Mesh.h"
#include "MeshElement.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"


#include "ResourceManager/ResourceManager.h"

namespace oakvr
{
	namespace render
	{
		
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

					auto it = m_shaders.find(pMeshElem->m_pMaterial->m_shaderName);
					if (it != std::end(m_shaders))
					{
						if (it->second.vs)
							UseShader(it->second.vs);
						if (it->second.ps)
							UseShader(it->second.ps);
						if (it->second.gs)
							UseShader(it->second.ds);
						if (it->second.ds)
							UseShader(it->second.ds);
						if (it->second.hs)
							UseShader(it->second.hs);
					}
					
					PrepareShaders();

					vb.Use(pMeshElem->m_vertexFormat);
					ib.Use();
					
					BindAdditionalShaderParams();
					if (pMeshElem->m_vecTextures.size())
						m_textures[pMeshElem->m_vecTextures[0]]->Use();

					DrawIndexed(pMeshElem->m_indexCount);
					//Draw(vertexCount);

					ib.Release();
					vb.Release();
					
				}
			}

			EndDraw();
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
		// --------------------------------------------------------------------------------
		void Renderer::RegisterTexture(const std::string &textureName, const std::shared_ptr<oakvr::core::MemoryBuffer> &buff)
		{
			if (buff.get() == nullptr)
				return;
			m_textures[textureName] = std::make_shared<Texture>(*buff);
		}

		// --------------------------------------------------------------------------------
		void Renderer::RegisterVertexShader(const std::string &shaderName, const std::shared_ptr<oakvr::core::MemoryBuffer> &buff)
		{
			if (buff.get() == nullptr)
				return;
			m_shaders[shaderName].vs = std::make_shared<Shader>(Shader::ShaderType::vertex, *buff);
		}

		// --------------------------------------------------------------------------------
		void Renderer::RegisterPixelShader(const std::string &shaderName, const std::shared_ptr<oakvr::core::MemoryBuffer> &buff)
		{
			if (buff.get() == nullptr)
				return;
			m_shaders[shaderName].ps = std::make_shared<Shader>(Shader::ShaderType::pixel, *buff);
		}

		// --------------------------------------------------------------------------------
		void Renderer::RegisterGeometryShader(const std::string &shaderName, const std::shared_ptr<oakvr::core::MemoryBuffer> &buff)
		{
			if (buff.get() == nullptr)
				return;
			m_shaders[shaderName].gs = std::make_shared<Shader>(Shader::ShaderType::geometry, *buff);
		}

		// --------------------------------------------------------------------------------
		void Renderer::RegisterDomainShader(const std::string &shaderName, const std::shared_ptr<oakvr::core::MemoryBuffer> &buff)
		{
			if (buff.get() == nullptr)
				return;
			m_shaders[shaderName].ds = std::make_shared<Shader>(Shader::ShaderType::domain, *buff);
		}

		// --------------------------------------------------------------------------------
		void Renderer::RegisterHullShader(const std::string &shaderName, const std::shared_ptr<oakvr::core::MemoryBuffer> &buff)
		{
			if (buff.get() == nullptr)
				return;
			m_shaders[shaderName].hs = std::make_shared<Shader>(Shader::ShaderType::hull, *buff);
		}
	}	// namespace render
}	// namespace oakvr