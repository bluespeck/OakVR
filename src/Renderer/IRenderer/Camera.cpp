
#include "Camera.h"

#include "Core/Math/Matrix.h"
#include "Renderer/IRenderer/AABB.h"

namespace Oak3D
{
	namespace Render
	{
		using Oak3D::Math::Vector3;

		// --------------------------------------------------------------------------------
		Camera::Camera()
		{	
		}

		// --------------------------------------------------------------------------------
		Camera::Camera(const Vector3 &pos, const Vector3 &look, const Vector3 &up)
		{
			m_position = pos;
			m_look = look;
			m_up = up;
		}

		// --------------------------------------------------------------------------------
		Camera::~Camera()
		{
		}

		// --------------------------------------------------------------------------------
		void Camera::Rotate( float x, float y, float z )
		{
			Oak3D::Math::Matrix matRotate;
			matRotate.SetYawPitchRoll(-y, -x, z);
			Oak3D::Math::Vector3 relativeLook = m_look - m_position;
			relativeLook = relativeLook * matRotate;
			m_look = m_position + relativeLook;
			
		}

		// --------------------------------------------------------------------------------
		void Camera::Translate(float x, float y, float z)
		{
			m_position.x += x; m_position.y += y; m_position.z += z;
			m_look.x += x; m_look.y += y; m_look.z += z;
		}

		// --------------------------------------------------------------------------------
		void Camera::Update(float dt)
		{		
		}

	}	// namespace Render
}	// namespace Oak3D