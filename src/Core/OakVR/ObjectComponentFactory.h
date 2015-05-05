#pragma once

#include <string>
#include <unordered_map>
#include <functional>

#include "ObjectComponent.h"

namespace oakvr
{
	class ObjectComponentFactory
	{
	public:
		static ObjectComponentSharedPointer MakeObjectComponent(const std::string objectComponentType, ObjectSharedPointer pObj ,ObjectComponentSharedPointer pDependeeComp = nullptr);
		


	public:
		static std::unordered_map<std::string, std::function<ObjectComponentSharedPointer(ObjectSharedPointer, ObjectComponentSharedPointer)>> s_objectComponentCreators;

	};

}