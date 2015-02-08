#pragma once

#include "ObjectComponent.h"

#include "Math/Vector3.h"
#include "Math/Matrix.h"

namespace oakvr
{
	class TransformComponent : public ObjectComponent
	{
	public:
		TransformComponent(ObjectSharedPointer pObj, ObjectComponentSharedPointer *pDependeeComponent=nullptr) : ObjectComponent{ pObj }, m_position( math::Vector3::Zero ), m_orientation( 0.0f, 0.0f, 1.0f ), m_scale( math::Vector3::One ) {}

		const math::Vector3 & GetPosition() { return m_position; }
		void SetPosition(const math::Vector3 &position) { m_position = position; }
		
		const math::Vector3 & GetOrientation() { return m_orientation; }
		void SetOrientation(const math::Vector3 &orientation) { m_orientation = orientation; }

		const math::Vector3 & GetScale() { return m_scale; }
		void SetScale(const math::Vector3 &scale) { m_scale = scale; }

	private:
		math::Vector3 m_position;
		math::Vector3 m_orientation;
		math::Vector3 m_scale;

		__OC_DECLARE_INITIALIZER
	};
}