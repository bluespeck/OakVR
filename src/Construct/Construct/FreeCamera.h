#include "OakVR/OakVR.h"

namespace construct
{
	class FreeCamera : public oakvr::render::Camera
	{
	public:
		FreeCamera(const std::string &id, const oakvr::math::Vector3 &pos, const oakvr::math::Vector3 &target, const oakvr::math::Vector3 &up) : oakvr::render::Camera(id, pos, target, up) {}
		FreeCamera(const std::string &id, const oakvr::math::Vector3 &pos, const oakvr::math::Vector3 &target, const oakvr::math::Vector3 &up, float strafeSpeed, float rotationSpeed) : oakvr::render::Camera(id, pos, target, up), m_strafeSpeed(strafeSpeed), m_rotationSpeed(rotationSpeed) {}

		auto Update(float dt) -> bool override;

		void SetStrafeSpeed(float newStrafeSpeed) { m_strafeSpeed = newStrafeSpeed; }
		void SetRotationSpeed(float newRotationSpeed) { m_rotationSpeed = newRotationSpeed; }
		auto GetStrafeSpeed() -> float{ return m_strafeSpeed;  }
		auto GetRotationSpeed() -> float { return m_rotationSpeed; }
	private:

		float m_strafeSpeed = 1.f;
		float m_rotationSpeed = 1.f;
	};
}