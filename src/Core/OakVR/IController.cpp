#include "IController.h"

namespace oakvr::core
{
	// --------------------------------------------------------------------------------
	auto IController::DeleteMe() -> void
	{
		delete this;
	}
}
