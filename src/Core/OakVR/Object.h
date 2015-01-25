#pragma once

#include <vector>
#include <unordered_map>

#include "Utils/StringId.h"
#include "Utils/Types.h"
#include "Math/Matrix.h"

namespace oakvr
{
	class Object;
	using ObjectSharedPointer = sp < Object > ;
	using ObjectUniquePointer = up < Object > ;
	using ObjectVector = std::vector < ObjectSharedPointer >;
	using ObjectMap = std::unordered_map < oakvr::StringId, ObjectSharedPointer > ;

	class Object
	{
	public:
		Object(); 	
		virtual ~Object();
		
		void AddChild(ObjectSharedPointer pObj);
		void RemoveChild(ObjectSharedPointer pObj);
		auto GetId() const -> const StringId &{ return m_objID; }
		auto GetParent() -> ObjectSharedPointer { return m_pParent; }
		auto GetChildren() -> const ObjectVector &{ return m_vecChildren; }
		void SetParent(ObjectSharedPointer pParent) { m_pParent = pParent; }

		auto GetRelativeTransform()->math::Matrix & { return m_matRelativeTransform; }
		void SetRelativeTransform(const math::Matrix &matRelativeTransform) { m_matRelativeTransform = matRelativeTransform; }


	public:
		// links to other objects
		ObjectSharedPointer m_pParent;
		ObjectVector m_vecChildren;
		math::Matrix m_matRelativeTransform = math::Matrix::Identity;

		StringId m_objID;
	};

	
} // namespace oakvr
