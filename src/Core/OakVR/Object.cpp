#include "Object.h"
#include "Utils/UniqueId.h"
#include <string>
#include <algorithm>
namespace oakvr
{
	Object::Object()
		:m_objID{ StringId(std::to_string(oakvr::core::UniqueId().Get()) + "OVR") }
	{

	}

	Object::~Object()
	{	
	}
	
	void Object::AddChild(ObjectSharedPointer pObj)
	{
		if (std::find(std::begin(m_vecChildren), std::end(m_vecChildren), pObj) == std::end(m_vecChildren))
			m_vecChildren.push_back(pObj);
	}

	void Object::RemoveChild(ObjectSharedPointer pObj)
	{
		m_vecChildren.erase(std::remove(std::begin(m_vecChildren), std::end(m_vecChildren), pObj));
	}

		

}	// namespace oakvr
