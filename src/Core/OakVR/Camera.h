#pragma once

#include "Object.h"
#include "Math/Matrix44.h"
#include "Math/Vector3.h"
#include "Frustum.h"
#include "Math/MathUtils.h"
#include "Updatable.h"
#include "Utils/StringId.h"

#include <initializer_list>


using oakvr::math::Vector3;
using oakvr::math::Matrix44;

namespace oakvr::render
{
	class Camera : public Updatable
	{
	public:
		Camera() = delete;
		Camera(const StringId&, const Vector3& pos, const Vector3& target, const Vector3& up);
		Camera(const StringId&, const std::initializer_list<Vector3>&);
		~Camera();

		auto ComputeFrustum() const->Frustum;

		auto ComputeViewMatrix() const->Matrix44;

		inline auto GetProjMatrix() const->Matrix44;

		inline auto Update(float dt) -> bool;

		inline auto GetPosition() const -> const Vector3&;
		inline auto GetForward() const -> const Vector3&;
		inline auto GetUp() const -> const Vector3&;
		inline auto GetRight() const->Vector3;

		inline auto SetPosition(const Vector3& position) -> void;
		inline auto SetLook(const Vector3& forward) -> void;
		inline auto SetUp(const Vector3& up) -> void;

		inline auto SetPerspectiveProjection(float fov, float aspectY, float nearDistance, float farDistance) -> void;
		inline auto SetPerspectiveProjection(float fov, float width, float height, float nearDistance, float farDistance) -> void;
		inline auto SetOrthographicProjection(float left, float right, float bottom, float top, float nearDistance, float farDistance) -> void;
		inline auto SetOrthographicProjection(float width, float height, float nearDistance, float farDistance) -> void;

		inline auto Translate(float x, float y, float z) -> void;
		inline auto Translate(const oakvr::math::Vector3& displacement) -> void;
		inline auto Rotate(float alpha, float beta, float gamma) -> void;	// angles around x,y,z axes [radians]

		auto OnRenderWindowSizeChanged(float newWidth, float newHeight) -> void;

		inline auto GetId() const -> const StringId&;

	private:
		StringId m_id;

	protected:
		Vector3 m_position;
		Vector3 m_forward;
		Vector3 m_up;

		// projection config
		float m_fov = 0.f;
		float m_rwWidth = 0.f;
		float m_rwHeight = 0.f;
		float m_near = 0.f;
		float m_far = 0.f;

		Matrix44	m_matProj;
	};

	using CameraSharedPointer = sp < Camera >;

	auto Camera::SetPerspectiveProjection(float fov, float aspectY, float nearDistance, float farDistance) -> void
	{
		m_matProj = Matrix44::PerspectiveProjection(fov, aspectY, nearDistance, farDistance);
		m_fov = fov;
		m_rwWidth = aspectY;
		m_rwHeight = 1;
		m_near = nearDistance;
		m_far = farDistance;
	}

	auto Camera::SetPerspectiveProjection(float fov, float width, float height, float nearDistance, float farDistance) -> void
	{
		m_matProj = Matrix44::PerspectiveProjection(fov, width, height, nearDistance, farDistance);
		m_fov = fov;
		m_rwWidth = width;
		m_rwHeight = height;
		m_near = nearDistance;
		m_far = farDistance;
	}

	auto Camera::SetOrthographicProjection(float left, float right, float bottom, float top, float nearDistance, float farDistance) -> void
	{
		m_matProj = Matrix44::OrthographicProjection(left, right, bottom, top, nearDistance, farDistance);
		m_fov = 0.f;
		m_rwWidth = right - left;
		m_rwHeight = top - bottom;
		m_near = nearDistance;
		m_far = farDistance;
	}

	auto Camera::SetOrthographicProjection(float width, float height, float nearDistance, float farDistance) -> void
	{
		m_matProj = Matrix44::OrthographicProjection(-width / 2, width / 2, -height / 2, height / 2, nearDistance, farDistance);
		m_fov = 0.f;
		m_rwWidth = width;
		m_rwHeight = height;
		m_near = nearDistance;
		m_far = farDistance;
	}

	auto Camera::SetPosition(const Vector3& position) -> void
	{
		m_position = position;
	}

	auto Camera::SetLook(const Vector3& forward) -> void
	{
		m_forward = forward;
	}

	auto Camera::SetUp(const Vector3& up) -> void
	{
		m_up = up;
	}

	auto Camera::GetProjMatrix() const -> Matrix44
	{
		return m_matProj;
	}

	auto Camera::Update(float dt)->bool
	{
		return true;
	}

	auto Camera::GetPosition() const -> const Vector3&
	{
		return m_position;
	}

	auto Camera::GetForward() const -> const Vector3&
	{
		return m_forward;
	}

	auto Camera::GetUp() const -> const Vector3&
	{
		return m_up;
	}

	auto Camera::GetRight() const ->Vector3
	{
		return m_up.Cross(m_forward);
	}

	auto Camera::Translate(float x, float y, float z) -> void
	{
		Translate({ x, y, z });
	}

	auto Camera::Translate(const Vector3& displacement) -> void
	{
		m_position += displacement;
	}

	auto Camera::Rotate(float alpha, float beta, float gamma) -> void
	{
		oakvr::math::Matrix44 matRotate;
		matRotate.SetYawPitchRoll(beta, alpha, gamma);
		m_forward = (m_forward * matRotate).GetNormalized();
		m_up = (m_up * matRotate).GetNormalized();
	}

	auto Camera::GetId() const -> const StringId&
	{
		return m_id;
	}
}