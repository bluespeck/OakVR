#include "IController.h"

namespace oakvr
{
	namespace Core
	{	
		// --------------------------------------------------------------------------------
		void IController::DeleteMe()
		{
			delete this;
		}
	} // namespace Core
}
