
#include "Camera.h"

#include "Math/Matrix.h"
#include "Renderer/Renderer/AABB.h"

namespace oakvr
{
	namespace render
	{
		using oakvr::math::Vector3;

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
		void Camera::Rotate( float alpha, float beta, float gamma )
		{
			oakvr::math::Matrix matRotate;
			matRotate.SetYawPitchRoll(beta, alpha, gamma);
			m_look = m_position + (m_look - m_position) * matRotate;
			m_up = (m_up * matRotate).GetNormalized();
		}

		// --------------------------------------------------------------------------------
		void Camera::Translate(float x, float y, float z)
		{
			oakvr::math::Vector3 direction = (m_look - m_position).GetNormalized();
			oakvr::math::Vector3 right = direction.Cross(m_up).GetNormalized();
			oakvr::math::Vector3 displacement = -x * right + -y * m_up + z * direction;
			m_position += displacement; 
			m_look += displacement;
		}

		// --------------------------------------------------------------------------------
		void Camera::Update(float dt)
		{		
		}

	}	// namespace Render
}	// namespace oakvr
