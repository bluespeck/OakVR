#include "Interface.h"

#include "OakVR.h"

#include "Renderer/Renderer/Mesh.h"
#include "Renderer/Renderer/MeshElement.h"

namespace oakvr::render
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

	auto RemoveMesh(const StringId &name) -> void
	{
		oakvr::OakVR::GetInstance().UnregisterMesh(GetMesh(name));
	}

	auto GetMesh(const StringId &name)->sp<oakvr::render::Mesh>
	{
		return oakvr::OakVR::GetInstance().GetRegisteredMesh(name);
	}

	auto TransformMesh(const StringId &name, const oakvr::math::Matrix44 &mat) -> void
	{
		oakvr::OakVR::GetInstance().TransformMesh(name, mat);
	}

	auto RegisterShader(const StringId &shaderName) -> void
	{
		oakvr::OakVR::GetInstance().RegisterShader(shaderName);
	}

	auto RegisterCamera(sp<oakvr::render::Camera> pCamera) -> void
	{
		oakvr::OakVR::GetInstance().RegisterCamera(pCamera);
	}

	auto UnregisterCamera(sp<oakvr::render::Camera> pCamera) -> void
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

	auto SetCurrentCamera(sp<oakvr::render::Camera> pCamera) -> void
	{
		oakvr::OakVR::GetInstance().SetCurrentCamera(pCamera);
	}

	auto SetCurrentCamera(const StringId &cameraId) -> void
	{
		oakvr::OakVR::GetInstance().SetCurrentCamera(cameraId);
	}
		
	auto SetRenderWindowPosition(int x, int y) -> void
	{
		oakvr::OakVR::GetInstance().SetRenderWindowPosition(x, y);
	}

	auto SetRenderWindowSize(unsigned int width, unsigned int height) -> void
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

	auto SetRenderWindowTitle(const std::string &title) -> void
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

	auto DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, float thickness, const  oakvr::render::Color &color) -> void
	{
		oakvr::OakVR::GetInstance().DrawLine(start, end, thickness, color);
	}

	auto DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, float thickness, const  oakvr::render::Color &color, const oakvr::render::Color &startColor) -> void
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
	
} // namespace oakvr::render

namespace oakvr::core
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

namespace oakvr
{
	auto RegisterUpdatable(sp<oakvr::Updatable> pUpdatable) -> void
	{
		oakvr::OakVR::GetInstance().RegisterUpdatable(pUpdatable);
	}

	auto UnregisterUpdatable(sp<oakvr::Updatable> pUpdatable) -> void
	{
		oakvr::OakVR::GetInstance().UnregisterUpdatable(pUpdatable);
	}
}