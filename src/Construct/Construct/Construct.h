#pragma once

#include "OakVR/Updatable.h"

namespace construct
{
	class Construct : public oakvr::Updatable
	{
	public:
		Construct();
		auto Update(float dt) -> bool;
	private:
		auto CreateTestMesh2() -> void;
		auto CreateTestMesh1() -> void;
		auto CreateTestMesh3() -> void;
		auto CreateTestMesh4() -> void;
		auto CreateTestMeshRoom() -> void;
	};
}