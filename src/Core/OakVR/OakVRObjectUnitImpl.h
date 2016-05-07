#pragma once

#include "OakVRObjectUnit.h"
#include "Octree.h"

namespace oakvr
{
	class OakVRObjectUnit::OakVRObjectUnitImpl
	{
	public:

	public:
		ObjectMap m_objectMap;
		ObjectVector m_objectVector;
		ObjectUniquePointer m_root;
		Octree<ObjectSharedPointer> m_octree;
	};
}
