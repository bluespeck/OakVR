#pragma once

#include "OakVR/Updateable.h"

namespace construct
{
	class Construct : public oakvr::Updateable
	{
	public:
		Construct();
		void Update(float dt) override;
	private:
		void CreateTestMesh1();
		void CreateTestMesh2();
	};
}