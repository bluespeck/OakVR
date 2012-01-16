#include "Button.h"

namespace Oak3D
{
	namespace Leaf3D
	{
		// --------------------------------------------------------------------------------
		Button::Button()
		{

		}

		void Button::OnMouseLeftButtonHeld(MouseEvent *mev)
		{
			if(m_bHasFocus)
			{
				m_position.y = mev->m_mouseData.m_mousePosition.y - 5;
				m_position.x = mev->m_mouseData.m_mousePosition.x - 5;
			}
			
		}
	}
}