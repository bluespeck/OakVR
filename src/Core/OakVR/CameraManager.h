#pragma once

#include "Camera.h"
#include "Utils/Types.h"
#include "Utils/StringId.h"

#include <vector>
#include <memory>



namespace oakvr::render
{
	class CameraManager
	{
	public:
		CameraManager();

		auto RegisterCamera(sp<Camera>) -> void;
		auto UnregisterCamera(sp<Camera>) -> void;

		sp<Camera> GetCamera(const StringId &cameraId);
		sp<Camera> GetCurrentCamera() { return m_currentCameraIndex < m_cameras.size() ? m_cameras[m_currentCameraIndex] : nullptr; }
		auto SetCurrentCamera(sp<Camera>) -> void;
		auto SetCurrentCamera(const StringId &cameraId) -> void;
	private:
		int m_currentCameraIndex = -1;
		std::vector<sp<Camera>> m_cameras;
	};
}
