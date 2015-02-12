#pragma once

#include <string>
#include <set>

#include "Utils/Types.h"

namespace oakvr
{
	class Object;
	using ObjectSharedPointer = sp < Object >;

	class ObjectComponent;
	using ObjectComponentSharedPointer = sp < ObjectComponent >;

	class ObjectComponent
	{

	public:

		ObjectComponent(ObjectSharedPointer pObject, ObjectComponentSharedPointer dependeeComponent = nullptr);
		virtual ~ObjectComponent();

		static std::set < std::string > & GetAllObjectComponentTypes();

		virtual std::string GetComponentTypeAsString() { return "unknown"; };

		ObjectSharedPointer GetObject() { return m_pObject; }
		void SetObject(ObjectSharedPointer pObj) { m_pObject = pObj; }

	private:

		ObjectSharedPointer m_pObject;
		static std::set < std::string > s_allObjectComponentTypes;
	};



#define _OC_DECLARE_INITIALIZER\
	public:																															\
		static ObjectComponentSharedPointer Create(ObjectSharedPointer, ObjectComponentSharedPointer dependentComponent = nullptr); \
		virtual std::string GetComponentTypeAsString();

#define _OC_DEFINE_INITIALIZER2(ocClassName, ocTypeStr)\
	_OAKVR_REGISTER_ENGINE_INITIALIZER([](){ std::cout<<"Transform or not!";ObjectComponentFactory::s_objectComponentCreators[ocTypeStr] = ocClassName::Create; }, ocClassName) \
	ObjectComponentSharedPointer ocClassName::Create(ObjectSharedPointer pObj, ObjectComponentSharedPointer dependentComponent) { return std::make_shared<ocClassName>(pObj, dependentComponent); }	\
	std::string ocClassName::GetComponentTypeAsString() { return ocTypeStr; }


#define _OC_DEFINE_INITIALIZER(componentType) _OC_DEFINE_INITIALIZER2(componentType ## Component, #componentType)

}

