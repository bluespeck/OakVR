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

		void CameraManager::RegisterCamera(std::shared_ptr<Camera> pCamera)
		{
			m_cameras.push_back(pCamera);
		}

		void CameraManager::UnregisterCamera(std::shared_ptr<Camera> pCamera)
		{
			auto it = std::find(m_cameras.begin(), m_cameras.end(), pCamera);
			if (it != m_cameras.end())
			{
				m_cameras.erase(it);
			}
			else
			{
				Log::PrintWarning("Trying to unregister a camera that was not registered before.");
			}
		}

		void CameraManager::SetCurrentCamera(std::shared_ptr<Camera> pCamera)
		{
			for (int i = 0; i < m_cameras.size(); ++i)
			{	
				if (m_cameras[i] == pCamera)
				{
					m_currentCameraIndex = i;
					return;
				}
			}
			Log::PrintError("Trying to set an unregistered camera as the current camera!");
		}

	}
}
