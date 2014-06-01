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
		std::shared_ptr<oakvr::render::Camera> GetCamera(const std::string &cameraId);
		std::shared_ptr<oakvr::render::Camera> GetCurrentCamera();
		void SetCurrentCamera(std::shared_ptr<oakvr::render::Camera> pCamera);
		void SetCurrentCamera(const std::string &cameraId);

		void DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, const  oakvr::render::Color &color);
		void DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, const  oakvr::render::Color &color, const oakvr::render::Color &startColor);

		void SetRenderWindowPosition(unsigned int x, unsigned int y);
		void SetRenderWindowSize(unsigned int width, unsigned int height);
		float GetRenderWindowWidth();
		float GetRenderWindowHeight();
		void SetRenderWindowTitle(const std::string &title);
		bool RenderWindowHasFocus();
		
	}

	void RegisterUpdateable(std::shared_ptr<oakvr::Updateable> pUpdateable);
	void UnregisterUpdateable(std::shared_ptr<oakvr::Updateable> pUpdateable);

	namespace core
	{
		void RegisterSubFolderPaths(const std::string &path);
		std::shared_ptr<oakvr::core::MemoryBuffer> GetResource(const std::string &id);
	}
} // namespace oakvr