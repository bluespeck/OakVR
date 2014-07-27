#pragma once

#include "OakVR/Updatable.h"

namespace construct
{
	class Construct : public oakvr::Updatable
	{
	public:
		Construct();
		auto Update(float dt) ->bool override;
	private:
		void CreateTestMesh1();
		void CreateTestMesh2();
		void CreateTestMesh3();
		void CreateTestMeshRoom();
	};
}