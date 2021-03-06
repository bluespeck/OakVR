#include "CameraManager.h"
#include "Log/Log.h"

#include <algorithm>

namespace oakvr
{
	namespace render
	{
		// --------------------------------------------------------------------------------
		CameraManager::CameraManager()
		{			
		}

		auto CameraManager::RegisterCamera(sp<Camera> pCamera) -> void
		{
			m_cameras.push_back(pCamera);
		}

		auto CameraManager::UnregisterCamera(sp<Camera> pCamera) -> void
		{
			auto size = m_cameras.size();
			m_cameras.erase(std::remove_if(std::begin(m_cameras), std::end(m_cameras), [&](const sp<Camera> &pRegisteredCamera)->bool{ return pRegisteredCamera == pCamera; }), std::begin(m_cameras));
			if (size == m_cameras.size())
			{
				Log::Warning("Trying to unregister a camera that was not registered before.");
			}
		}

		sp<Camera> CameraManager::GetCamera(const StringId &cameraId)
		{
			auto it = std::find_if(m_cameras.begin(), m_cameras.end(), [&](sp<Camera> &e) { return e->GetId() == cameraId; });
			if (it != m_cameras.end())
				return *it;
			
			Log::Warning("Could not find camera with id = %s !", cameraId.c_str());
			return nullptr;
		}

		auto CameraManager::SetCurrentCamera(sp<Camera> pCamera) -> void
		{
			for (int i = 0; i < m_cameras.size(); ++i)
			{	
				if (m_cameras[i] == pCamera)
				{
					m_currentCameraIndex = i;
					return;
				}
			}
			Log::Error("Trying to set an unregistered camera (%s) as the current camera!", pCamera->GetId());
		}

		auto CameraManager::SetCurrentCamera(const StringId &cameraId) -> void
		{
			for (int i = 0; i < m_cameras.size(); ++i)
			{
				if (m_cameras[i]->GetId() == cameraId)
				{
					m_currentCameraIndex = i;
					return;
				}
			}
			Log::Error("Trying to set an unregistered camera (%s) as the current camera!", cameraId.c_str());
		}
	}
}
