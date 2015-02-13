#include "ObjectComponentFactory.h"

#include "OakVR.h"
#include "TransformComponent.h"
#include "VisualComponent.h"


#define _OC_COMPONENT_INITIALIZER2(ocClassName, ocTypeStr) _OAKVR_REGISTER_ENGINE_INITIALIZER([](){ ObjectComponentFactory::s_objectComponentCreators[ocTypeStr] = ocClassName::_Create; }, ocClassName)
#define _OC_COMPONENT_INITIALIZER(componentType) _OC_COMPONENT_INITIALIZER2(componentType ## Component, #componentType)


namespace oakvr
{
	_OC_COMPONENT_INITIALIZER(Transform);
	_OC_COMPONENT_INITIALIZER(Visual);

	std::unordered_map<std::string, std::function<ObjectComponentSharedPointer(ObjectSharedPointer, ObjectComponentSharedPointer)>> ObjectComponentFactory::s_objectComponentCreators;

	ObjectComponentSharedPointer ObjectComponentFactory::MakeObjectComponent(const std::string objectComponentType, ObjectSharedPointer pObj, ObjectComponentSharedPointer pDependeeComp /*= nullptr*/)
	{	
		auto it = s_objectComponentCreators.find(objectComponentType);

		if (it != s_objectComponentCreators.end())
		{
			return it->second(pObj, pDependeeComp);
		}

		return nullptr;
	}
}
