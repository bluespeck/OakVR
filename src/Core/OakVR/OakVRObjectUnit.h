#pragma once

#include "Utils/Types.h"
#include "Utils/StringId.h"

#include "OakVR/Object.h"

#include "Math/Matrix.h"

namespace oakvr
{
	class OakVRObjectUnit
	{
	public:
		void AddObject(ObjectSharedPointer pObject, const StringId &parentId);
		void RemoveObject(const StringId &name);
		ObjectSharedPointer FindObject(const StringId &objectId);
		void TransferObject(const StringId &id, const StringId &newParentId);

	protected:
		ObjectMap m_objectMap;
	};
}