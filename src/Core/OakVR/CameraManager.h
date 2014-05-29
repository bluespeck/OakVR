#pragma once

#include "Camera.h"

#include <vector>
#include <memory>



namespace oakvr
{
	namespace render
	{
		class CameraManager
		{
		public:
			CameraManager();

			void RegisterCamera(std::shared_ptr<Camera>);
			void UnregisterCamera(std::shared_ptr<Camera>);

			std::shared_ptr<Camera> GetCamera(const std::string &cameraId);
			std::shared_ptr<Camera> GetCurrentCamera() { return m_currentCameraIndex < m_cameras.size() ? m_cameras[m_currentCameraIndex] : nullptr; }
			void SetCurrentCamera(std::shared_ptr<Camera>);
			void SetCurrentCamera(const std::string &cameraId);
		private:
			int m_currentCameraIndex;
			std::vector<std::shared_ptr<Camera>> m_cameras;
		};
	}
}
