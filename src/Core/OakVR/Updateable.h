#pragma once

namespace oakvr
{
	class Updateable
	{
	public:
		Updateable() {}
		virtual ~Updateable() {}
		virtual void Update(float dt) = 0; /* override in derived class to add custom behavior */
	};
}