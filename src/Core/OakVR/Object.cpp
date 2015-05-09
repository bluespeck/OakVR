#include "Object.h"

#include <string>
#include <algorithm>

#include "Utils/UniqueId.h"

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
}	// namespace oakvr
