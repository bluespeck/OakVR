
#include "MouseEvent.h"

namespace Oak3D
{
	namespace Leaf3D
	{
		MouseEvent::MouseEvent(ScreenPosition mousePosition)
		: Event(nullptr)
		, m_mousePosition(mousePosition)
		{

		}

		ScreenPosition MouseEvent::GetMousePos()
		{
			return m_mousePosition;
		}
	}
}
