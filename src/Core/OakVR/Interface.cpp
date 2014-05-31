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

		void RegisterCamera(std::shared_ptr<oakvr::render::Camera> pCamera)
		{
			oakvr::OakVR::GetInstance().RegisterCamera(pCamera);
		}

		void UnregisterCamera(std::shared_ptr<oakvr::render::Camera> pCamera)
		{
			oakvr::OakVR::GetInstance().UnregisterCamera(pCamera);
		}

		std::shared_ptr<oakvr::render::Camera> GetCamera(const std::string &cameraId)
		{
			return oakvr::OakVR::GetInstance().GetCamera(cameraId);
		}

		std::shared_ptr<oakvr::render::Camera> GetCurrentCamera()
		{
			return oakvr::OakVR::GetInstance().GetCurrentCamera();
		}

		void SetCurrentCamera(std::shared_ptr<oakvr::render::Camera> pCamera)
		{
			oakvr::OakVR::GetInstance().SetCurrentCamera(pCamera);
		}

		void SetCurrentCamera(const std::string &cameraId)
		{
			oakvr::OakVR::GetInstance().SetCurrentCamera(cameraId);
		}
		
		void SetRenderWindowPosition(unsigned int x, unsigned int y)
		{
			oakvr::OakVR::GetInstance().SetRenderWindowPosition(x, y);
		}

		void SetRenderWindowSize(unsigned int width, unsigned int height)
		{
			oakvr::OakVR::GetInstance().SetRenderWindowSize(width, height);
		}

		void SetRenderWindowTitle(const std::string &title)
		{
			oakvr::OakVR::GetInstance().SetRenderWindowTitle(title);
		}

		bool RenderWindowHasFocus()
		{
			return oakvr::OakVR::GetInstance().HasFocus();
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