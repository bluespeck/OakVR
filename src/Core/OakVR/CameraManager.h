#pragma once

#include <list>
#include "Camera.h"

namespace oakvr
{
	namespace render
	{
		class CameraManager
		{
		public:
			CameraManager();

			Camera *GetCurrentCamera() { return m_pCurrentCamera; }
			void SetAsCurrentCamera(Camera *pCamera) { m_pCurrentCamera = pCamera; }

		private:
			Camera *m_pCurrentCamera;
			std::list<Camera *> m_cameras;
		};
	}
}
