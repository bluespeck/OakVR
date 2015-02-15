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
		auto AddObjectToGraph(ObjectSharedPointer pObject, const StringId &parentId) -> void;
		auto RemoveObjectFromGraph(const StringId &name) -> void;
		ObjectSharedPointer FindObject(const StringId &objectId);
		auto TransferObject(const StringId &id, const StringId &newParentId) -> void;

	protected:
		ObjectMap m_objectMap;
	};
}