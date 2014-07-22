#include "Interface.h"

#include "OakVR.h"

#include "Renderer/Renderer/Mesh.h"
#include "Renderer/Renderer/MeshElement.h"

namespace oakvr
{
	namespace render
	{	
		auto CreateMesh(const std::string &name, const oakvr::render::VertexDescriptor &vertexDescriptor, const oakvr::core::MemoryBuffer &vertexBuffer, uint8_t indexStride, const oakvr::core::MemoryBuffer &indexBuffer, std::shared_ptr<Material> pMaterial, std::vector<std::string> textureNames)
			-> std::shared_ptr<oakvr::render::Mesh>
		{
			auto pMeshElem = std::make_shared<oakvr::render::MeshElement>(vertexDescriptor, vertexBuffer, indexStride, indexBuffer, pMaterial, textureNames);
			
			auto pMesh = std::make_shared<oakvr::render::Mesh>(name);
			pMesh->AddMeshElement(pMeshElem);
			oakvr::OakVR::GetInstance().RegisterMesh(pMesh);
			oakvr::render::RegisterShader(pMaterial->m_shaderName);

			return pMesh;
		}

		auto CreateMesh(const std::string &name, const std::string &resourceId, std::shared_ptr<oakvr::render::Material> pMaterial) -> std::shared_ptr<oakvr::render::Mesh>
		{
			auto pMeshBuffer = oakvr::core::GetResource(resourceId);
			auto pMesh = oakvr::OakVR::GetInstance().CreateMesh(name, pMeshBuffer, pMaterial);
			oakvr::OakVR::GetInstance().RegisterMesh(pMesh);
			oakvr::render::RegisterShader(pMaterial->m_shaderName);
			return pMesh;
		}

		void RemoveMesh(const std::string &name)
		{
			oakvr::OakVR::GetInstance().UnregisterMesh(GetMesh(name));
		}

		auto GetMesh(const std::string &name)->std::shared_ptr<oakvr::render::Mesh>
		{
			return oakvr::OakVR::GetInstance().GetRegisteredMesh(name);
		}

		void TransformMesh(const std::string &name, const oakvr::math::Matrix &mat)
		{
			oakvr::OakVR::GetInstance().TransformMesh(name, mat);
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

		auto GetCamera(const std::string &cameraId)->std::shared_ptr<oakvr::render::Camera>
		{
			return oakvr::OakVR::GetInstance().GetCamera(cameraId);
		}

		auto GetCurrentCamera()->std::shared_ptr<oakvr::render::Camera>
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
		
		void SetRenderWindowPosition(int x, int y)
		{
			oakvr::OakVR::GetInstance().SetRenderWindowPosition(x, y);
		}

		void SetRenderWindowSize(unsigned int width, unsigned int height)
		{
			oakvr::OakVR::GetInstance().SetRenderWindowSize(width, height);
		}

		auto GetRenderWindowPositionX()->int
		{
			return oakvr::OakVR::GetInstance().GetRenderWindowPositionX();
		}

		auto GetRenderWindowPositionY()->int
		{
			return oakvr::OakVR::GetInstance().GetRenderWindowPositionY();
		}

		auto GetRenderWindowWidth()->float
		{
			return oakvr::OakVR::GetInstance().GetRenderWindowWidth();
		}

		auto GetRenderWindowHeight()->float
		{
			return oakvr::OakVR::GetInstance().GetRenderWindowHeight();
		}

		void SetRenderWindowTitle(const std::string &title)
		{
			oakvr::OakVR::GetInstance().SetRenderWindowTitle(title);
		}

		auto RenderWindowHasFocus()->bool
		{
			return oakvr::OakVR::GetInstance().HasFocus();
		}

		void DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, float thickness, const  oakvr::render::Color &color)
		{
			oakvr::OakVR::GetInstance().DrawLine(start, end, thickness, color);
		}

		void DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, float thickness, const  oakvr::render::Color &color, const oakvr::render::Color &startColor)
		{
			oakvr::OakVR::GetInstance().DrawLine(start, end, thickness, color, startColor);
		}
	}

	namespace core
	{
		void RegisterSubFolderPaths(const std::string &path)
		{
			oakvr::OakVR::GetInstance().RegisterSubFolderPaths(path);
		}

		auto GetResource(const std::string &id)->std::shared_ptr<oakvr::core::MemoryBuffer>
		{
			return oakvr::OakVR::GetInstance().GetResource(id);
		}
	}

	void RegisterUpdatable(std::shared_ptr<oakvr::Updatable> pUpdatable)
	{
		oakvr::OakVR::GetInstance().RegisterUpdatable(pUpdatable);
	}

	void UnregisterUpdatable(std::shared_ptr<oakvr::Updatable> pUpdatable)
	{
		oakvr::OakVR::GetInstance().UnregisterUpdatable(pUpdatable);
	}

} // namespace oakvr