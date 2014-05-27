#pragma once

namespace oakvr
{
	class Updateable
	{
	public:
		Updateable() {}
		virtual ~Updateable() {}
		virtual void Update(double dt) = 0; /* override in derived class to add custom behavior */
	};
}