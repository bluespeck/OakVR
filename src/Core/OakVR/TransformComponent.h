#pragma once

#include "ObjectComponent.h"

#include "Math/Vector3.h"
#include "Math/Matrix.h"

namespace oakvr
{
	class TransformComponent : public ObjectComponent
	{
	public:
		TransformComponent(ObjectSharedPointer pObj, ObjectComponentSharedPointer pDependeeComponent = nullptr);

		auto GetPosition() -> const math::Vector3 &;
		void SetPosition(const math::Vector3 &position);
		
		auto GetOrientation() -> const math::Vector3 &;
		void SetOrientation(const math::Vector3 &orientation);

		auto GetScale() -> const math::Vector3 &;
		void SetScale(const math::Vector3 &scale);

	private:
		math::Vector3 m_position;
		math::Vector3 m_orientation;
		math::Vector3 m_scale;

		_OC_DECLARE_INITIALIZER_HELPERS(Transform)
	};

	inline auto TransformComponent::GetPosition()->const math::Vector3 &
	{
		return m_position;
	}
	
	inline void TransformComponent::SetPosition(const math::Vector3 &position)
	{
		m_position = position;
	}

	inline auto TransformComponent::GetOrientation()->const math::Vector3 &
	{
		return m_orientation;
	}

	inline void TransformComponent::SetOrientation(const math::Vector3 &orientation)
	{
		m_orientation = orientation;
	}

	inline auto TransformComponent::GetScale()->const math::Vector3 &
	{
		return m_scale;
	}

	inline void TransformComponent::SetScale(const math::Vector3 &scale)
	{
		m_scale = scale;
	}
}