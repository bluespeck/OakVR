#pragma once

#include "Utils\Types.h"

namespace oakvr
{
	class Updatable
	{
	public:
		Updatable() {}
		virtual ~Updatable() {}
		virtual auto Update(float dt) ->bool = 0; /* override in derived class to add custom behavior */
	};

	using UpdateableSharedPointer = sp < Updatable > ;
	using UpdatableUniquePointer = up < Updatable > ;
}