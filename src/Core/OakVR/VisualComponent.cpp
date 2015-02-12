#include "VisualComponent.h"

#include <iostream>

#include "Interface.h"
#include "ObjectComponentFactory.h"
#include "OakVR.h"

namespace oakvr
{
	//_OC_DEFINE_INITIALIZER(Visual, __COUNTER__)

	void VisualComponent::SetMeshFromResource(StringId resourceId)
	{
		auto pMesh = oakvr::render::GetMesh(GetObject()->GetId());

	}

}