
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
		Camera::Camera(const std::string& cameraId, const Vector3 &pos, const Vector3 &target, const Vector3 &up)
			: m_id{ cameraId }
			, m_position{ pos }
			, m_forward{ (target - pos).GetNormalized() }
			, m_up{ up.GetNormalized() }
		{
		}

		Camera::Camera(const std::string &cameraId, const std::initializer_list<Vector3> &initList)
			: m_id{ cameraId }
		{
			if (initList.size() >= 3)
			{
				m_position = *(initList.begin());
				m_forward = (*(initList.begin() + 1) - m_position).GetNormalized();
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
			m_forward = (m_forward * matRotate).GetNormalized();
			m_up = (m_up * matRotate).GetNormalized();
		}
				
		oakvr::math::Matrix Camera::ComputeViewMatrix() const
		{
			auto zaxis = m_forward.GetNormalized();
			auto xaxis = GetRight().GetNormalized();
			auto yaxis = zaxis.Cross(xaxis).GetNormalized();

			oakvr::math::Matrix mat;
			mat._11 = xaxis.x;			mat._12 = yaxis.x;			mat._13 = zaxis.x;			mat._14 = 0.f;
			mat._21 = xaxis.y;			mat._22 = yaxis.y;			mat._23 = zaxis.y;			mat._24 = 0.f;
			mat._31 = xaxis.z;			mat._32 = yaxis.z;			mat._33 = zaxis.z;			mat._34 = 0.f;
			mat._41 = -xaxis.Dot(m_position);	mat._42 = -yaxis.Dot(m_position);	mat._43 = -zaxis.Dot(m_position);	mat._44 = 1.f;
			
			return mat;
		}

	}	// namespace Render
}	// namespace oakvr
