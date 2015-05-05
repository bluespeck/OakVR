#include "VisualComponent.h"

#include "Interface.h"
#include "ObjectComponentFactory.h"
#include "OakVR.h"

namespace oakvr
{
	auto VisualComponent::SetMeshFromResource(StringId resourceId) -> void
	{
		m_pMesh = oakvr::render::GetMesh(GetObject()->GetId());
	}

}