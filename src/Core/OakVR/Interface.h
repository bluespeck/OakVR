#pragma once

#include "Utils/RendererUtils.h"
#include "Renderer/Renderer/Material.h"
#include "OakVR/Camera.h"
#include "Renderer/Renderer/Mesh.h"

#include "Updatable.h"

#include "Utils/Buffer.h"

#include <memory>
#include <vector>


namespace oakvr
{
	namespace render
	{
		typedef std::vector<oakvr::render::VertexElementDescriptor> VertexDescriptor;
				
		auto CreateMesh(const std::string &name, const oakvr::render::VertexDescriptor &vertexDescriptor, 
			const oakvr::core::MemoryBuffer &vertexBuffer, uint8_t indexStride, const oakvr::core::MemoryBuffer &indexBuffer,	
			std::shared_ptr<Material> pMaterial, std::vector<std::string> textureNames // for each texcoord
			)->std::shared_ptr<oakvr::render::Mesh>;
		auto CreateMesh(const std::string &name, const std::string &resourceId, std::shared_ptr<oakvr::render::Material> pMaterial)->std::shared_ptr<oakvr::render::Mesh>;
		void RemoveMesh(const std::string &name);
		auto GetMesh(const std::string &name)->std::shared_ptr<oakvr::render::Mesh>;
		void TransformMesh(const std::string &name, const oakvr::math::Matrix &mat);

		void RegisterShader(const std::string &shaderName);

		void RegisterCamera(std::shared_ptr<oakvr::render::Camera> pCamera);
		void UnregisterCamera(std::shared_ptr<oakvr::render::Camera> pCamera);
		auto GetCamera(const std::string &cameraId)->std::shared_ptr<oakvr::render::Camera>;
		auto GetCurrentCamera()->std::shared_ptr<oakvr::render::Camera>;
		void SetCurrentCamera(std::shared_ptr<oakvr::render::Camera> pCamera);
		void SetCurrentCamera(const std::string &cameraId);

		void DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, float thickness, const  oakvr::render::Color &color);
		void DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, float thickness, const  oakvr::render::Color &color, const oakvr::render::Color &startColor);

		void SetRenderWindowPosition(int x, int y);
		void SetRenderWindowSize(unsigned int width, unsigned int height);
		auto GetRenderWindowPositionX()->int;
		auto GetRenderWindowPositionY()->int;
		auto GetRenderWindowWidth()->float;
		auto GetRenderWindowHeight()->float;
		void SetRenderWindowTitle(const std::string &title);
		auto RenderWindowHasFocus()->bool;
		
	}

	void RegisterUpdatable(std::shared_ptr<oakvr::Updatable> pUpdatable);
	void UnregisterUpdatable(std::shared_ptr<oakvr::Updatable> pUpdatable);

	namespace core
	{
		void RegisterSubFolderPaths(const std::string &path);
		auto GetResource(const std::string &id)->std::shared_ptr<oakvr::core::MemoryBuffer>;
	}
} // namespace oakvr