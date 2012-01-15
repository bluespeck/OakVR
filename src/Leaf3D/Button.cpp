#include "Button.h"

namespace Oak3D
{
	namespace Leaf3D
	{
		// --------------------------------------------------------------------------------
		Button::Button()
		{

		}

		void Button::OnMouseMoved(MouseEvent *mev)
		{
			m_position = mev->m_mouseData.m_mousePosition;
		}
	}
}