#include "VisualComponent.h"

#include "Interface.h"
#include "ObjectComponentFactory.h"

namespace oakvr
{
	__OC_DEFINE_INITIALIZER(Visual)

	void VisualComponent::SetMeshFromResource(StringId resourceId)
	{
		auto pMesh = oakvr::render::GetMesh(GetObject()->GetId());

	}

}