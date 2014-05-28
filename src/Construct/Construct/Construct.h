#pragma once

#include "OakVR/Updateable.h"

namespace construct
{
	class Construct : public oakvr::Updateable
	{
	public:
		Construct();
		void Update(double dt) override;
	private:
		void CreateTestMesh();
	};
}