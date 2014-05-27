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

	void RegisterUpdateable(std::shared_ptr<oakvr::Updateable> pUpdateable)
	{
		oakvr::OakVR::GetInstance().RegisterUpdateable(pUpdateable);
	}

	void UnregisterUpdateable(std::shared_ptr<oakvr::Updateable> pUpdateable)
	{
		oakvr::OakVR::GetInstance().UnregisterUpdateable(pUpdateable);
	}

} // namespace oakvr