
#include "Clickable.h"

namespace Oak3D
{
	namespace Leaf3D
	{
		Clickable::Clickable()
		{			
			m_onPressHandler = [](){};
			m_onReleaseHandler = [](){};
			m_onHoverHandler = [](){};
			
		}
	}
}
