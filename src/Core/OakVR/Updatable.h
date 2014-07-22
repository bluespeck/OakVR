#pragma once

namespace oakvr
{
	class Updatable
	{
	public:
		Updatable() {}
		virtual ~Updatable() {}
		virtual void Update(float dt) = 0; /* override in derived class to add custom behavior */
	};
}