#pragma once

#include "Utils/Types.h"
#include "Utils/StringId.h"

#include "OakVR/Object.h"

#include "Math/Matrix.h"

namespace oakvr
{
	class OakVRObjectComponent
	{
	public:
		void AddObject(ObjectSharedPointer pObject, const StringId &parentId, const math::Matrix &relativeTransform);
		void RemoveObject(const StringId &name);
		ObjectSharedPointer FindObject(const StringId &objectId);
		void TransferObject(const StringId &id, const StringId &newParentId, const math::Matrix &newRelativeTransform = math::Matrix::Identity);

	protected:
		ObjectMap m_objectMap;
	};
}