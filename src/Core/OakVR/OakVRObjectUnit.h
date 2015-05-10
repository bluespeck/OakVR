#pragma once

#include "Utils/Types.h"
#include "Utils/StringId.h"

#include "OakVR/Object.h"

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
		//auto GetAllObjects() -> ObjectVector &;
		//auto GetAllObjects() const -> const ObjectVector &;

		OakVRObjectUnit();
		~OakVRObjectUnit();
	protected:
		class OakVRObjectUnitImpl;
		up<OakVRObjectUnitImpl> m_pImpl;
	};
}