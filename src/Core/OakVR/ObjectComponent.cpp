#include "ObjectComponent.h"

namespace oakvr
{
	std::set < std::string > ObjectComponent::s_allObjectComponentTypes;

	ObjectComponent::ObjectComponent(ObjectSharedPointer pObject, ObjectComponentSharedPointer dependeeComponent/* = nullptr*/)
		:m_pObject{ pObject }
	{
	}

	ObjectComponent::~ObjectComponent()
	{

	}

	auto ObjectComponent::GetAllObjectComponentTypes() -> std::set < std::string > &
	{
		static std::set < std::string > s_ObjectComponentTypes;
		return s_ObjectComponentTypes;
	}
	
} // namespace oakvr