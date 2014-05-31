#include "OakVR/OakVR.h"

namespace construct
{
	class FreeCamera : public oakvr::render::Camera
	{
	public:
		FreeCamera(const std::string &id, const oakvr::math::Vector3 &pos, const oakvr::math::Vector3 &target, const oakvr::math::Vector3 &up) : oakvr::render::Camera(id, pos, target, up) {}
		FreeCamera(const std::string &id, const oakvr::math::Vector3 &pos, const oakvr::math::Vector3 &target, const oakvr::math::Vector3 &up, float strafeSpeed, float rotationSpeed) : oakvr::render::Camera(id, pos, target, up), m_strafeSpeed(strafeSpeed), m_rotationSpeed(rotationSpeed) {}

		void Update(float dt) override;

		void SetStrafeSpeed(float newStrafeSpeed) { m_strafeSpeed = newStrafeSpeed; }
		void SetRotationSpeed(float newRotationSpeed) { m_rotationSpeed = newRotationSpeed; }
		float GetStrafeSpeed() { return m_strafeSpeed;  }
		float GetRotationSpeed() { return m_rotationSpeed; }
	private:

		float m_strafeSpeed = 1.f;
		float m_rotationSpeed = 1.f;
	};
}