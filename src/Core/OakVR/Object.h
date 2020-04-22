#pragma once

#include <vector>
#include <unordered_map>
#include <memory>

#include "Utils/StringId.h"
#include "Utils/Types.h"
#include "Math/Matrix44.h"

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
		
		template <typename ComponentType>
		auto AddComponent() -> std::shared_ptr<ComponentType>;

		template <typename ComponentType>
		auto GetComponent() -> std::shared_ptr<ComponentType>;

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

	template <typename ComponentType>
	auto Object::AddComponent() -> std::shared_ptr<ComponentType>
	{
		auto pObjComp = std::make_shared<ComponentType>(shared_from_this());
		auto componentTypeName = ComponentType::GetComponentClassTypeAsString();

		m_componentMap[componentTypeName] = std::static_pointer_cast<ObjectComponent>(pObjComp);

		return pObjComp;
	}

	template <typename ComponentType>
	auto Object::GetComponent() -> std::shared_ptr<ComponentType>
	{
		auto componentTypeName = ComponentType::GetComponentClassTypeAsString();
		auto it = m_componentMap.find(componentTypeName);
		if (it != m_componentMap.end())
			return std::dynamic_pointer_cast<ComponentType>(it->second);
		else
			return nullptr;
	}

} // namespace oakvr
