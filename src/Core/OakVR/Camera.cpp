
#include "Camera.h"

#include "Math/Matrix.h"
#include "Renderer/Renderer/AABB.h"

#include "Log/Log.h"

namespace oakvr::render
{
	using oakvr::math::Vector3;

	// --------------------------------------------------------------------------------
	Camera::Camera(const StringId& cameraId, const Vector3& pos, const Vector3& target, const Vector3& up)
		: m_id(cameraId)
		, m_position(pos)
	{
		m_forward = (target - pos).GetNormalized();
		auto s = m_forward.Cross(up).GetNormalized();
		m_up = s.Cross(m_forward);
	}

	Camera::Camera(const StringId& cameraId, const std::initializer_list<Vector3>& initList)
		: m_id(cameraId)
	{
		if (initList.size() >= 3)
		{
			m_position = *(initList.begin());
			m_forward = (*(initList.begin() + 1) - m_position).GetNormalized();
			auto s = m_forward.Cross(*(initList.begin() + 2)).GetNormalized();
			m_up = s.Cross(m_forward);
		}
		else
		{
			Log::Error("Trying to initialize camera with incomplete initializer list!");
		}
	}

	// --------------------------------------------------------------------------------
	Camera::~Camera()
	{
	}

	auto Camera::ComputeViewMatrix() const -> oakvr::math::Matrix
	{
		auto zaxis = -m_forward.GetNormalized();
		auto xaxis = -GetRight().GetNormalized();
		auto yaxis = zaxis.Cross(xaxis).GetNormalized();


		oakvr::math::Matrix mat;
		mat._11 = xaxis.x;			mat._12 = xaxis.y;			mat._13 = xaxis.z;			mat._14 = -xaxis.Dot(m_position);
		mat._21 = yaxis.x;			mat._22 = yaxis.y;			mat._23 = yaxis.z;			mat._24 = -yaxis.Dot(m_position);
		mat._31 = zaxis.x;			mat._32 = zaxis.y;			mat._33 = zaxis.z;			mat._34 = -zaxis.Dot(m_position);
		mat._41 = 0.f;				mat._42 = 0.f;				mat._43 = 0.f;				mat._44 = 1.f;

		//mat._11 = xaxis.x;			mat._12 = yaxis.x;			mat._13 = zaxis.x;			mat._14 = 0.f;
		//mat._21 = xaxis.y;			mat._22 = yaxis.y;			mat._23 = zaxis.y;			mat._24 = 0.f;
		//mat._31 = xaxis.z;			mat._32 = yaxis.z;			mat._33 = zaxis.z;			mat._34 = 0.f ;
		//mat._41 = -xaxis.Dot(m_position); mat._42 = -yaxis.Dot(m_position); mat._43 = -zaxis.Dot(m_position); mat._44 = 1.f;

		return mat;
	}

	auto Camera::ComputeFrustum() const -> Frustum
	{
		Frustum f;
		using oakvr::math::Vector3;

		if (m_fov < 1e-6f)
		{
			Vector3 right = GetRight();
			float halfWidth = m_rwWidth / 2;
			float halfHeight = m_rwHeight / 2;
			f.m_planes[Frustum::nearIndex].normal = m_forward;
			f.m_planes[Frustum::nearIndex].w = (m_position + m_near * m_forward).Dot(f.m_planes[Frustum::nearIndex].normal);
			f.m_planes[Frustum::farIndex].normal = -m_forward;
			f.m_planes[Frustum::farIndex].w = (m_position + m_far * m_forward).Dot(f.m_planes[Frustum::farIndex].normal);
			f.m_planes[Frustum::leftIndex].normal = right;
			f.m_planes[Frustum::leftIndex].w = (m_position - halfWidth * right).Dot(f.m_planes[Frustum::leftIndex].normal);
			f.m_planes[Frustum::rightIndex].normal = -right;
			f.m_planes[Frustum::rightIndex].w = (m_position + halfWidth * right).Dot(f.m_planes[Frustum::rightIndex].normal);
			f.m_planes[Frustum::bottomIndex].normal = m_up;
			f.m_planes[Frustum::bottomIndex].w = (m_position - halfHeight * m_up).Dot(f.m_planes[Frustum::bottomIndex].normal);
			f.m_planes[Frustum::topIndex].normal = -m_up;
			f.m_planes[Frustum::topIndex].w = (m_position + halfHeight * m_up).Dot(f.m_planes[Frustum::topIndex].normal);
		}
		else
		{
			f.m_planes[Frustum::nearIndex].normal = m_forward;
			f.m_planes[Frustum::nearIndex].w = (m_position + m_near * m_forward).Dot(f.m_planes[Frustum::nearIndex].normal);
			f.m_planes[Frustum::farIndex].normal = -m_forward;
			f.m_planes[Frustum::farIndex].w = (m_position + m_far * m_forward).Dot(f.m_planes[Frustum::farIndex].normal);

			{
				float halfWidth = m_near * tanf(m_fov);
				Vector3 right = GetRight();
				Vector3 tLeft = (m_forward * m_near - right * halfWidth).GetNormalized();
				Vector3 tRight = (m_forward * m_near + right * halfWidth).GetNormalized();

				f.m_planes[Frustum::leftIndex].normal = Vector3{ tLeft.z, tLeft.y, -tLeft.x };
				f.m_planes[Frustum::leftIndex].w = m_position.Dot(f.m_planes[Frustum::leftIndex].normal);
				f.m_planes[Frustum::rightIndex].normal = Vector3{ -tRight.z, tRight.y, tRight.x };
				f.m_planes[Frustum::rightIndex].w = m_position.Dot(f.m_planes[Frustum::rightIndex].normal);
			}

			float halfHeight = m_near * tanf(m_fov); // TODO: maybe multiply with aspect ratio here
			Vector3 tBottom = (m_forward * m_near - m_up * halfHeight).GetNormalized();
			Vector3 tTop = (m_forward * m_near + m_up * halfHeight).GetNormalized();

			f.m_planes[Frustum::bottomIndex].normal = Vector3{ tBottom.x, -tBottom.z, tBottom.y };
			f.m_planes[Frustum::bottomIndex].w = m_position.Dot(f.m_planes[Frustum::bottomIndex].normal);
			f.m_planes[Frustum::topIndex].normal = Vector3{ tTop.x, tTop.z, tTop.y };
			f.m_planes[Frustum::topIndex].w = m_position.Dot(f.m_planes[Frustum::topIndex].normal);
		}
		return f;
	}

	auto Camera::OnRenderWindowSizeChanged(float newWidth, float newHeight) -> void
	{
		if (fabs(m_matProj._44) > 1e-9)
		{
			SetOrthographicProjection(newWidth, newHeight, m_near, m_far);
		}
		else
		{
			SetPerspectiveProjection(m_fov, newWidth, newHeight, m_near, m_far);
		}
	}
}