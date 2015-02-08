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



#define __OC_DECLARE_INITIALIZER\
	private:																													\
	static struct __ObjectComponentInitializer { __ObjectComponentInitializer(); } s_initializer;								\
	public:																														\
	static ObjectComponentSharedPointer Create(ObjectSharedPointer, ObjectComponentSharedPointer dependantComponent = nullptr); \
	virtual std::string GetComponentTypeAsString();

#define __OC_DEFINE_INITIALIZER2(ocClassName, ocTypeStr)\
	ocClassName::__ObjectComponentInitializer ocClassName::s_initializer;										\
	ocClassName::__ObjectComponentInitializer::__ObjectComponentInitializer() { ObjectComponentFactory::s_objectComponentCreators[ocTypeStr] = ocClassName::Create; } \
	ObjectComponentSharedPointer ocClassName::Create(ObjectSharedPointer pObj, ObjectComponentSharedPointer dependantComponent /*= nullptr */) { return std::make_shared<ocClassName>(pObj, dependantComponent); }	\
	std::string ocClassName::GetComponentTypeAsString() { return ocTypeStr; }

#define __OC_DEFINE_INITIALIZER(componentType) __OC_DEFINE_INITIALIZER2(componentType ## Component, #componentType)
}