#pragma once

#include "Camera.h"
#include "Utils/Types.h"

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

			void RegisterCamera(sp<Camera>);
			void UnregisterCamera(sp<Camera>);

			sp<Camera> GetCamera(const std::string &cameraId);
			sp<Camera> GetCurrentCamera() { return m_currentCameraIndex < m_cameras.size() ? m_cameras[m_currentCameraIndex] : nullptr; }
			void SetCurrentCamera(sp<Camera>);
			void SetCurrentCamera(const std::string &cameraId);
		private:
			int m_currentCameraIndex = -1;
			std::vector<sp<Camera>> m_cameras;
		};
	}
}
