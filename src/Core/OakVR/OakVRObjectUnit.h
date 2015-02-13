#pragma once

#include "Utils/Types.h"
#include "Utils/StringId.h"

#include "OakVR/Object.h"
#include "OakVR/ObjectComponents.h"

#include "Math/Matrix.h"

namespace oakvr
{
	class OakVRObjectUnit
	{
	public:
		ObjectSharedPointer CreateObject(const StringId &name);
		void AddObjectToGraph(ObjectSharedPointer pObject, const StringId &parentId);
		void RemoveObjectFromGraph(const StringId &name);
		ObjectSharedPointer FindObject(const StringId &objectId);
		void TransferObject(const StringId &id, const StringId &newParentId);

	protected:
		ObjectMap m_objectMap;
	};
}