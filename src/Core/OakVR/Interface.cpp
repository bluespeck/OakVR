#include "Interface.h"

#include "OakVR.h"

#include "Renderer/Renderer/Mesh.h"
#include "Renderer/Renderer/MeshElement.h"

namespace oakvr
{
	namespace render
	{	
		void CreateMesh(const oakvr::render::VertexDescriptor &vertexDescriptor, const oakvr::core::MemoryBuffer &vertexBuffer, uint8_t indexStride, const oakvr::core::MemoryBuffer &indexBuffer, std::shared_ptr<Material> pMaterial,	std::vector<std::string> textureNames)
		{
			auto pMeshElem = std::make_shared<oakvr::render::MeshElement>(vertexDescriptor, vertexBuffer, indexStride, indexBuffer, pMaterial, textureNames);
			
			auto pMesh = std::make_shared<oakvr::render::Mesh>();
			pMesh->AddMeshElement(pMeshElem);
			oakvr::OakVR::GetInstance().RegisterMesh(pMesh);
		}

		void RegisterShader(const std::string &shaderName)
		{
			oakvr::OakVR::GetInstance().RegisterShader(shaderName);
		}
	}

	namespace core
	{
		void RegisterSubFolderPaths(const std::string &path)
		{
			oakvr::OakVR::GetInstance().RegisterSubFolderPaths(path);
		}

		std::shared_ptr<oakvr::core::MemoryBuffer> GetResource(const std::string &id)
		{
			return oakvr::OakVR::GetInstance().GetResource(id);
		}
	}

	void RegisterUpdateable(std::shared_ptr<oakvr::Updateable> pUpdateable)
	{
		oakvr::OakVR::GetInstance().RegisterUpdateable(pUpdateable);
	}

	void UnregisterUpdateable(std::shared_ptr<oakvr::Updateable> pUpdateable)
	{
		oakvr::OakVR::GetInstance().UnregisterUpdateable(pUpdateable);
	}

} // namespace oakvr