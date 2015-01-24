#pragma once

#include <vector>

#include "Utils/StringId.h"
#include "Utils/Types.h"

namespace oakvr
{
	class Object;
	using ObjectSharedPointer = sp < Object > ;
	using ObjectUniquePointer = up < Object > ;
	using ObjectVector = std::vector < ObjectSharedPointer >;

	class Object
	{
	public:
		Object( void ); 	
		virtual ~Object( void );
		void AddChild(ObjectSharedPointer pObj);

		

	public:
		// links to other objects
		ObjectSharedPointer m_pParent;
		ObjectVector m_children;

		oakvr::StringId m_objID;
	};

	
} // namespace oakvr
