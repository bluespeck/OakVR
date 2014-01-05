#include "IController.h"

namespace oakvr
{
	namespace core
	{	
		// --------------------------------------------------------------------------------
		void IController::DeleteMe()
		{
			delete this;
		}
	} // namespace core
}
