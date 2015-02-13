#include "VisualComponent.h"

#include "Interface.h"
#include "ObjectComponentFactory.h"
#include "OakVR.h"

namespace oakvr
{
	_OC_DEFINE_INITIALIZER_HELPERS(Visual)

	void VisualComponent::SetMeshFromResource(StringId resourceId)
	{
		m_pMesh = oakvr::render::GetMesh(GetObject()->GetId());

	}

}