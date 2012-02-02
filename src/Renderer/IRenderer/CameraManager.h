#ifndef __OAK3D_INCLUDE_RENDER_CAMERAMANAGER_H__
#define __OAK3D_INCLUDE_RENDER_CAMERAMANAGER_H__

#include <list>
#include "Camera.h"

namespace Oak3D
{
	namespace Render
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

#endif
