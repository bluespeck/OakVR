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
		auto FindObject(const StringId &objectId) -> ObjectSharedPointer;
		auto TransferObject(const StringId &id, const StringId &newParentId) -> void;
		inline auto GetAllObjects() -> ObjectVector &;
		inline auto GetAllObjects() const -> const ObjectVector &;
	protected:
		ObjectMap m_objectMap;
		ObjectVector m_objectVector;
	};

	auto OakVRObjectUnit::GetAllObjects() -> ObjectVector &
	{
		return m_objectVector;
	}

	auto OakVRObjectUnit::GetAllObjects() const -> const ObjectVector &
	{
		return m_objectVector;
	}
}