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

		static auto GetAllObjectComponentTypes() -> std::set < std::string > &;

		virtual auto GetComponentTypeAsString() -> std::string {
																return "unknown"; };

		auto GetObject() -> ObjectSharedPointer;
		auto SetObject(ObjectSharedPointer pObj) -> void;

	private:

		ObjectSharedPointer m_pObject;
		static std::set < std::string > s_allObjectComponentTypes;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	inline auto ObjectComponent::GetObject() -> ObjectSharedPointer 
	{ 
		return m_pObject; 
	}

	inline auto ObjectComponent::SetObject(ObjectSharedPointer pObj) -> void
	{
		m_pObject = pObj;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _OC_DECLARE_INITIALIZER_HELPERS2(ocClassName, ocTypeStr)\
	public:																															\
		static auto As ## ocClassName(ObjectComponentSharedPointer pComp)->sp < ocClassName >;										\
		virtual std::string GetComponentTypeAsString();																				\
	private:																														\
	static ObjectComponentSharedPointer _Create(ObjectSharedPointer, ObjectComponentSharedPointer dependentComponent = nullptr);	\
	friend struct OakVREngineInitializer ## ocClassName;


#define _OC_DEFINE_INITIALIZER_HELPERS2(ocClassName, ocTypeStr)\
	ObjectComponentSharedPointer ocClassName::_Create(ObjectSharedPointer pObj, ObjectComponentSharedPointer dependentComponent) { return std::make_shared<ocClassName>(pObj, dependentComponent); }\
	auto ocClassName::As ## ocClassName(ObjectComponentSharedPointer pComp)->sp < ocClassName > { return std::static_pointer_cast<ocClassName>(pComp); }											\
	std::string ocClassName::GetComponentTypeAsString() { return ocTypeStr; }


#define _OC_DECLARE_INITIALIZER_HELPERS(componentType) _OC_DECLARE_INITIALIZER_HELPERS2(componentType ## Component, #componentType)
#define _OC_DEFINE_INITIALIZER_HELPERS(componentType) _OC_DEFINE_INITIALIZER_HELPERS2(componentType ## Component, #componentType)

}

