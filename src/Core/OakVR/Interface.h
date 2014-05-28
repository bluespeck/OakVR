#pragma once

#include "Renderer/Renderer/RendererUtils.h"
#include "Renderer/Renderer/Material.h"
#include "OakVR/Camera.h"

#include "Updateable.h"

#include "Utils/Buffer.h"

#include <memory>
#include <vector>


namespace oakvr
{
	namespace render
	{
		typedef std::vector<oakvr::render::VertexElementDescriptor> VertexDescriptor;
				
		void CreateMesh(
			const oakvr::render::VertexDescriptor &vertexDescriptor,
			const oakvr::core::MemoryBuffer &vertexBuffer,
			uint8_t indexStride,
			const oakvr::core::MemoryBuffer &indexBuffer,
			std::shared_ptr<Material> pMaterial,
			std::vector<std::string> textureNames // for each texcoord
			);

		void RegisterShader(const std::string &shaderName);

		void RegisterCamera(std::shared_ptr<oakvr::render::Camera> pCamera);
		void UnregisterCamera(std::shared_ptr<oakvr::render::Camera> pCamera);
		std::shared_ptr<oakvr::render::Camera> GetCurrentCamera();
		void SetCurrentCamera(std::shared_ptr<oakvr::render::Camera> pCamera);
	}

	void RegisterUpdateable(std::shared_ptr<oakvr::Updateable> pUpdateable);
	void UnregisterUpdateable(std::shared_ptr<oakvr::Updateable> pUpdateable);

	namespace core
	{
		void RegisterSubFolderPaths(const std::string &path);
		std::shared_ptr<oakvr::core::MemoryBuffer> GetResource(const std::string &id);
	}
} // namespace oakvr