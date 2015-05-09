#pragma once

#include "ObjectComponent.h"

#include "Math/Vector3.h"
#include "Math/Matrix.h"
#include <string>

namespace oakvr
{
	class TransformComponent : public ObjectComponent
	{
	public:
		TransformComponent(ObjectSharedPointer pObj);

		auto GetPosition() -> const math::Vector3 &;
		auto SetPosition(const math::Vector3 &position) -> void;
		
		auto GetOrientation() -> const math::Vector3 &;
		auto SetOrientation(const math::Vector3 &orientation) -> void;

		auto GetScale() -> const math::Vector3 &;
		auto SetScale(const math::Vector3 &scale) -> void;

		virtual	auto GetComponentObjectType() const noexcept -> oakvr::ObjectComponentId override { return oakvr::ObjectComponentId::transform; }
		virtual	auto GetComponentObjectTypeAsString() const noexcept -> std::string override { return "TransformComponent"s; }

		static	auto GetComponentClassType() noexcept -> oakvr::ObjectComponentId { return oakvr::ObjectComponentId::transform; }
		static 	auto GetComponentClassTypeAsString() noexcept -> std::string { return "TransformComponent"s; }

	private:
		math::Vector3 m_position;
		math::Vector3 m_orientation;
		math::Vector3 m_scale;

	};

	using TransformComponentSharedPointer = sp < TransformComponent > ;

	inline auto TransformComponent::GetPosition()->const math::Vector3 &
	{
		return m_position;
	}
	
	inline auto TransformComponent::SetPosition(const math::Vector3 &position) -> void
	{
		m_position = position;
	}

	inline auto TransformComponent::GetOrientation()->const math::Vector3 &
	{
		return m_orientation;
	}

	inline auto TransformComponent::SetOrientation(const math::Vector3 &orientation) -> void
	{
		m_orientation = orientation;
	}

	inline auto TransformComponent::GetScale()->const math::Vector3 &
	{
		return m_scale;
	}

	inline auto TransformComponent::SetScale(const math::Vector3 &scale) -> void
	{
		m_scale = scale;
	}
}