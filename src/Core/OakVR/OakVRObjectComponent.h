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
		void AddObject(const StringId &name, const StringId &parentName, const math::Matrix &relativeTransform);
		void RemoveObject(const StringId &name);
		ObjectSharedPointer FindObject(const StringId &name);
		void TransferObject(const StringId &name, const StringId &newParentName, const math::Matrix &newRelativeTransform = math::Matrix::Identity);
	};
}