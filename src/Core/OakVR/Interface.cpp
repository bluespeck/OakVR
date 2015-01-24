#include "Interface.h"

#include "OakVR.h"

#include "Renderer/Renderer/Mesh.h"
#include "Renderer/Renderer/MeshElement.h"

namespace oakvr
{
	namespace render
	{	
		auto CreateMesh(const StringId &name, const oakvr::render::VertexDescriptor &vertexDescriptor, const oakvr::core::MemoryBuffer &vertexBuffer, uint8_t indexStride, const oakvr::core::MemoryBuffer &indexBuffer, sp<Material> pMaterial, std::vector<StringId> textureNames)
			-> sp<oakvr::render::Mesh>
		{
			auto pMeshElem = std::make_shared<oakvr::render::MeshElement>(vertexDescriptor, vertexBuffer, indexStride, indexBuffer, pMaterial, textureNames);
			
			auto pMesh = std::make_shared<oakvr::render::Mesh>(name);
			pMesh->AddMeshElement(pMeshElem);
			oakvr::OakVR::GetInstance().RegisterMesh(pMesh);
			oakvr::render::RegisterShader(pMaterial->m_shaderName);

			return pMesh;
		}

		auto CreateMesh(const StringId &name, const StringId &resourceId, sp<oakvr::render::Material> pMaterial) -> sp<oakvr::render::Mesh>
		{
			auto pMeshBuffer = oakvr::core::GetResource(resourceId);
			auto pMesh = oakvr::OakVR::GetInstance().CreateMesh(name, pMeshBuffer, pMaterial);
			oakvr::OakVR::GetInstance().RegisterMesh(pMesh);
			oakvr::render::RegisterShader(pMaterial->m_shaderName);
			return pMesh;
		}

		void RemoveMesh(const StringId &name)
		{
			oakvr::OakVR::GetInstance().UnregisterMesh(GetMesh(name));
		}

		auto GetMesh(const StringId &name)->sp<oakvr::render::Mesh>
		{
			return oakvr::OakVR::GetInstance().GetRegisteredMesh(name);
		}

		void TransformMesh(const StringId &name, const oakvr::math::Matrix &mat)
		{
			oakvr::OakVR::GetInstance().TransformMesh(name, mat);
		}

		void RegisterShader(const StringId &shaderName)
		{
			oakvr::OakVR::GetInstance().RegisterShader(shaderName);
		}

		void RegisterCamera(sp<oakvr::render::Camera> pCamera)
		{
			oakvr::OakVR::GetInstance().RegisterCamera(pCamera);
		}

		void UnregisterCamera(sp<oakvr::render::Camera> pCamera)
		{
			oakvr::OakVR::GetInstance().UnregisterCamera(pCamera);
		}

		auto GetCamera(const StringId &cameraId)->sp<oakvr::render::Camera>
		{
			return oakvr::OakVR::GetInstance().GetCamera(cameraId);
		}

		auto GetCurrentCamera()->sp<oakvr::render::Camera>
		{
			return oakvr::OakVR::GetInstance().GetCurrentCamera();
		}

		void SetCurrentCamera(sp<oakvr::render::Camera> pCamera)
		{
			oakvr::OakVR::GetInstance().SetCurrentCamera(pCamera);
		}

		void SetCurrentCamera(const StringId &cameraId)
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
			return static_cast<int>(oakvr::OakVR::GetInstance().GetRenderWindowPositionX());
		}

		auto GetRenderWindowPositionY()->int
		{
			return static_cast<int>(oakvr::OakVR::GetInstance().GetRenderWindowPositionY());
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

		auto ScreenCoordsToWindowClient(oakvr::math::Vector2 screenPos)->oakvr::math::Vector2
		{
			return oakvr::math::Vector2{
				screenPos.x - oakvr::render::GetRenderWindowPositionX() - oakvr::render::GetRenderWindowWidth() / 2.f
				, (oakvr::render::GetRenderWindowHeight() - (screenPos.y - oakvr::render::GetRenderWindowPositionY())) - oakvr::render::GetRenderWindowHeight() / 2.f
			};
		}

		void DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, float thickness, const  oakvr::render::Color &color)
		{
			oakvr::OakVR::GetInstance().DrawLine(start, end, thickness, color);
		}

		void DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, float thickness, const  oakvr::render::Color &color, const oakvr::render::Color &startColor)
		{
			oakvr::OakVR::GetInstance().DrawLine(start, end, thickness, color, startColor);
		}

#define IMPLEMENT_DISABLEENABLE_FCT(paramName) \
		void Enable ## paramName ()\
		{\
			oakvr::OakVR::GetInstance().Enable ## paramName();\
		}\
		\
		void Disable ## paramName ()\
		{\
			oakvr::OakVR::GetInstance().Disable ## paramName();\
		}\
		\
		void Toggle ## paramName ()\
		{\
			oakvr::OakVR::GetInstance().Toggle ## paramName();\
		}\
		\
		bool Is ## paramName ## Enabled()\
		{\
			return oakvr::OakVR::GetInstance().Is ## paramName ## Enabled();\
		}
		
		IMPLEMENT_DISABLEENABLE_FCT(Wireframe)
		IMPLEMENT_DISABLEENABLE_FCT(Culling)
		IMPLEMENT_DISABLEENABLE_FCT(DepthTest)
		IMPLEMENT_DISABLEENABLE_FCT(Blending)
	
	}

	namespace core
	{
		auto RegisterSubFolderPaths(const std::string &path)->bool
		{
			return oakvr::OakVR::GetInstance().RegisterSubFolderPaths(path);
		}

		auto GetResource(const StringId &id)->sp<oakvr::core::MemoryBuffer>
		{
			return oakvr::OakVR::GetInstance().GetResource(id);
		}
	}

	void RegisterUpdatable(sp<oakvr::Updatable> pUpdatable)
	{
		oakvr::OakVR::GetInstance().RegisterUpdatable(pUpdatable);
	}

	void UnregisterUpdatable(sp<oakvr::Updatable> pUpdatable)
	{
		oakvr::OakVR::GetInstance().UnregisterUpdatable(pUpdatable);
	}

} // namespace oakvr