#include "IController.h"

namespace Oak3D
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