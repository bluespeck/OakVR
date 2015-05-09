#pragma once

#include <string>

#include "Utils/Types.h"
#include "ObjectComponents.h"

using namespace std::literals::string_literals;

namespace oakvr
{
	class Object;
	using ObjectSharedPointer = sp < Object >;

	class ObjectComponent;
	using ObjectComponentSharedPointer = sp < ObjectComponent >;

	class ObjectComponent
	{

	public:

		ObjectComponent(ObjectSharedPointer pObject) : m_pObject{ pObject } {};

		virtual	~ObjectComponent() = default;
		
		virtual	auto GetComponentObjectType() const -> oakvr::ObjectComponentId { return oakvr::ObjectComponentId::object; }
		virtual	auto GetComponentObjectTypeAsString() const -> std::string { return "ObjectComponent"s; }

		static	auto GetComponentClassType() -> oakvr::ObjectComponentId { return oakvr::ObjectComponentId::object; }
		static 	auto GetComponentClassTypeAsString() -> std::string { return "ObjectComponent"s; }

		auto GetObject() -> ObjectSharedPointer;
		auto SetObject(ObjectSharedPointer pObj) -> void;

	private:

		ObjectSharedPointer m_pObject;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	inline auto ObjectComponent::GetObject() -> ObjectSharedPointer 
	{ 
		return m_pObject; 
	}

	inline auto ObjectComponent::SetObject(ObjectSharedPointer pObj) -> void
	{
		m_pObject = pObj;
	}
}

