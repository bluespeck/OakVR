#pragma once

#include <vector>
#include <unordered_map>

#include "Utils/StringId.h"
#include "Utils/Types.h"
#include "Math/Matrix.h"

#include "ObjectComponent.h"

namespace oakvr
{
	class Object;
	using ObjectSharedPointer = sp < Object > ;
	using ObjectUniquePointer = up < Object > ;
	using ObjectVector = std::vector < ObjectSharedPointer >;
	using ObjectMap = std::unordered_map < oakvr::StringId, ObjectSharedPointer > ;

	class Object: public std::enable_shared_from_this<Object>
	{

	public:

		Object();
		Object(const StringId &name);
		virtual ~Object();
		
		auto GetId() const -> const StringId &;

		auto AddChild(ObjectSharedPointer pObj) -> void;
		auto RemoveChild(ObjectSharedPointer pObj) -> void;
		auto GetChildren() -> const ObjectVector &;
		auto GetParent()->ObjectSharedPointer;
		auto SetParent(ObjectSharedPointer pParent) -> void;
		
		

		auto AddComponent(const std::string &componentName) -> void;
		auto GetComponent(const std::string &componentName)->ObjectComponentSharedPointer;

	public:

		ObjectSharedPointer m_pParent;
		ObjectVector m_vecChildren;
		StringId m_objID;

		std::unordered_map<std::string, ObjectComponentSharedPointer> m_componentMap;
		
	};

	inline auto Object::GetId() const -> const StringId &
	{ 
		return m_objID; 
	}

	inline auto Object::GetChildren() -> const ObjectVector &
	{ 
		return m_vecChildren; 
	}

	inline auto Object::GetParent() -> ObjectSharedPointer
	{
		return m_pParent;
	}

	inline auto Object::SetParent(ObjectSharedPointer pParent) -> void
	{ 
		m_pParent = pParent; 
	}

} // namespace oakvr
