#include "FreeCamera.h"
#include "Input/KeyboardInput/KeyboardInput.h"
#include "Input/MouseInput/MouseInput.h"
#include "Math/Vector2.h"
#include "Math/MathUtils.h"

namespace construct
{
	auto FreeCamera::Update(float dt)->bool
	{
		if (oakvr::render::RenderWindowHasFocus() && !oakvr::input::keyboard::GetCaptor())
		{
			if (oakvr::input::keyboard::IsDown(oakvr::input::Key::s))
			{
				m_position -= m_strafeSpeed * dt * m_forward;
			}
			if (oakvr::input::keyboard::IsDown(oakvr::input::Key::w))
			{
				m_position += m_strafeSpeed * dt * m_forward;
			}			
			if (oakvr::input::keyboard::IsDown(oakvr::input::Key::a))
			{
				m_position += m_strafeSpeed * dt * GetRight();
			}
			if (oakvr::input::keyboard::IsDown(oakvr::input::Key::d))
			{
				m_position -= m_strafeSpeed * dt * GetRight();
			}
			if (oakvr::input::keyboard::IsDown(oakvr::input::Key::space) )
			{
				if(oakvr::input::keyboard::IsDown(oakvr::input::Key::lShift) || oakvr::input::keyboard::IsDown(oakvr::input::Key::rShift))
				{
					m_position -= m_strafeSpeed * dt * m_up;
				}
				else
				{
					m_position += m_strafeSpeed * dt * m_up;
				}
			}

			if (oakvr::input::keyboard::IsDown(oakvr::input::Key::lShift) || oakvr::input::keyboard::IsDown(oakvr::input::Key::rShift))
			{
				oakvr::math::Vector2 delta = oakvr::input::mouse::GetPositionDelta();
				delta.Normalize();

				auto mRotationAroundRightDir = oakvr::math::Matrix::RotationAxisRightHanded(delta.y * m_rotationSpeed * dt, GetRight());
				auto mRotationAroundUpDir = oakvr::math::Matrix::RotationAxisRightHanded(-delta.x * m_rotationSpeed * dt, m_up);
				m_forward = (m_forward * mRotationAroundUpDir * mRotationAroundRightDir).GetNormalized();
				m_up = (m_up * mRotationAroundRightDir).GetNormalized();
			}
		}
		return true;
	}
}