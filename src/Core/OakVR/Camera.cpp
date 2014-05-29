
#include "Camera.h"

#include "Math/Matrix.h"
#include "Renderer/Renderer/AABB.h"

#include "Log/Log.h"

namespace oakvr
{
	namespace render
	{
		using oakvr::math::Vector3;

		// --------------------------------------------------------------------------------
		Camera::Camera(const std::string& cameraId, const Vector3 &pos, const Vector3 &look, const Vector3 &up)
			: m_id { cameraId }
			, m_position{ pos }
			, m_look{look}
			, m_up{up}
		{
		}

		Camera::Camera(const std::string &cameraId, const std::initializer_list<Vector3> &initList)
			: m_id{ cameraId }
		{
			if (initList.size() >= 3)
			{
				m_position = *(initList.begin());
				m_look = *(initList.begin() + 1);
				m_up = *(initList.begin() + 2);
			}
			else
			{
				Log::PrintError("Trying to initialize camera with incomplete initializer list!");
			}
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

		oakvr::math::Matrix Camera::ComputeViewMatrix() const
		{
			auto target = GetLook();
			auto up = GetUp();
			auto eye = GetPosition();
			
			auto zaxis = (eye - target).GetNormalized();
			auto xaxis = up.Cross(zaxis).GetNormalized();
			auto yaxis = zaxis.Cross(xaxis);

			oakvr::math::Matrix mat;
			mat._11 = xaxis.x;			mat._12 = yaxis.x;			mat._13 = zaxis.x;			mat._14 = 0.f;
			mat._21 = xaxis.y;			mat._22 = yaxis.y;			mat._23 = zaxis.y;			mat._24 = 0.f;
			mat._31 = xaxis.z;			mat._32 = yaxis.z;			mat._33 = zaxis.z;			mat._34 = 0.f;
			mat._41 = -xaxis.Dot(eye);	mat._42 = -yaxis.Dot(eye);	mat._43 = zaxis.Dot(eye);	mat._44 = 1.f;
		
			return mat;
		}

	}	// namespace Render
}	// namespace oakvr
