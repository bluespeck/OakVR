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
		virtual ~Object();
		
		void AddChild(ObjectSharedPointer pObj);
		void RemoveChild(ObjectSharedPointer pObj);
		auto GetId() const -> const StringId &{ return m_objID; }
		auto GetParent() -> ObjectSharedPointer { return m_pParent; }
		auto GetChildren() -> const ObjectVector &{ return m_vecChildren; }
		void SetParent(ObjectSharedPointer pParent) { m_pParent = pParent; }

		void AddComponent(const std::string &componentName);
		auto GetComponent(const std::string &componentName)->ObjectComponentSharedPointer;

	public:

		ObjectSharedPointer m_pParent;
		ObjectVector m_vecChildren;
		StringId m_objID;

		std::unordered_map<std::string, ObjectComponentSharedPointer> m_componentMap;
		
	};

	
} // namespace oakvr
