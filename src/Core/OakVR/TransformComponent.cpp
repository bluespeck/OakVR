#include "TransformComponent.h"

#include <iostream>

#include "ObjectComponentFactory.h"
#include "OakVR.h"

namespace oakvr
{
	
	_OC_DEFINE_INITIALIZER(Transform);

	TransformComponent::TransformComponent(ObjectSharedPointer pObj, ObjectComponentSharedPointer pDependeeComponent)
	: ObjectComponent{ pObj }, m_position(math::Vector3::Zero), m_orientation(0.0f, 0.0f, 1.0f), m_scale(math::Vector3::One) 
	{
	}
	
}
