#include "IController.h"

namespace oakvr
{
	namespace core
	{	
		// --------------------------------------------------------------------------------
		auto IController::DeleteMe() -> void
		{
			delete this;
		}
	} // namespace core
}
