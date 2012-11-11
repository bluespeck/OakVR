#include "IController.h"

namespace ro3d
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