#pragma once

#include <string>
#include <set>

#include "Utils/Types.h"

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

		ObjectComponent(ObjectSharedPointer pObject);
		virtual ~ObjectComponent() = default;

		virtual auto GetComponentObjectTypeAsString() -> std::string { return "ObjectComponent"s; }
		static auto GetComponentClassTypeAsString() -> std::string { return "ObjectComponent"s; }

		auto GetObject() -> ObjectSharedPointer;
		auto SetObject(ObjectSharedPointer pObj) -> void;

	private:

		ObjectSharedPointer m_pObject;
		static std::set < std::string > s_allObjectComponentTypes;
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

