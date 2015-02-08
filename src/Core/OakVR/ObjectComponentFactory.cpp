#include "ObjectComponentFactory.h"

namespace oakvr
{
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