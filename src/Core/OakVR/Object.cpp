#include "Object.h"
#include "Utils/UniqueId.h"
#include <string>
#include <algorithm>

#include "ObjectComponentFactory.h"

namespace oakvr
{
	Object::Object()
		:m_objID{ StringId(std::to_string(oakvr::core::UniqueId().Get()) + "OVR") }
	{

	}

	Object::Object(const StringId &objId)
		:m_objID{ objId }
	{

	}

	Object::~Object()
	{
	}

	auto Object::AddChild(ObjectSharedPointer pObj) -> void
	{
		if (std::find(std::begin(m_vecChildren), std::end(m_vecChildren), pObj) == std::end(m_vecChildren))
			m_vecChildren.push_back(pObj);
	}

	auto Object::RemoveChild(ObjectSharedPointer pObj) -> void
	{
		m_vecChildren.erase(std::remove(std::begin(m_vecChildren), std::end(m_vecChildren), pObj));
	}

	auto Object::AddComponent(const std::string &componentName) -> void
	{
		auto pComponent = GetComponent(componentName);
		if (!pComponent)
		{
			if (componentName == "Visual")
			{
				m_componentMap[componentName] = ObjectComponentFactory::MakeObjectComponent(componentName, shared_from_this(), GetComponent("Transform"));
			}
			else
			{
				m_componentMap[componentName] = ObjectComponentFactory::MakeObjectComponent(componentName, shared_from_this());
			}
		}
	}

	auto Object::GetComponent(const std::string &componentName)->ObjectComponentSharedPointer
	{
		auto it = m_componentMap.find(componentName);
		if (it != m_componentMap.end())
			return it->second;
		return nullptr;
	}

}	// namespace oakvr
