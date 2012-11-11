
#include <algorithm>

#include "Widget.h"


namespace ro3d
{
	namespace Leaf3D
	{
		std::list<Widget *> *Widget::s_widgets = nullptr;
		bool Widget::s_bDeleteListIfEmpty = false;

		// --------------------------------------------------------------------------------
		Widget::Widget()
		: m_bVisible(true)
		, IFocusable()
		{
			GetWidgetList()->push_back(this);
		}

		// --------------------------------------------------------------------------------
		Widget::~Widget()
		{
			// TODO will the equality be ok?
			s_widgets->erase(std::find(s_widgets->begin(), s_widgets->end(), this));
			if(s_bDeleteListIfEmpty && s_widgets->size() == 0)
				delete s_widgets;

		}

		// --------------------------------------------------------------------------------
		FocusZone Widget::GetFocusZone()
		{
			return FocusZone(m_position, m_size, m_depth);
		}
		
		// --------------------------------------------------------------------------------
		void Widget::OnMouseLeftButtonPressed(MouseEvent *mev)
		{
			if(m_bHasFocus)
			{
				this->CaptureMouse();
			}

		}

		// --------------------------------------------------------------------------------
		void Widget::OnMouseLeftButtonHeld(MouseEvent *mev)
		{
			if(m_bHasFocus)
			{
				m_position = mev->m_mouseData.m_mousePosition;
				m_position.x -= 50;
				m_position.y -= 50;
			}
			
		}

		// --------------------------------------------------------------------------------
		void Widget::OnMouseLeftButtonReleased(MouseEvent *mev)
		{
			if(m_bHasFocus)
			{
				this->ReleaseMouse();
			}

		}

	}
}