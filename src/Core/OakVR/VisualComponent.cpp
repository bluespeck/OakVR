#include "VisualComponent.h"

#include "Interface.h"
#include "ObjectComponentFactory.h"
#include "OakVR.h"

namespace oakvr
{
	_OC_DEFINE_INITIALIZER_HELPERS(Visual)

	auto VisualComponent::SetMeshFromResource(StringId resourceId) -> void
	{
		m_pMesh = oakvr::render::GetMesh(GetObject()->GetId());

	}

}