
#include <algorithm>

#include "Widget.h"


namespace Oak3D
{
	namespace Leaf3D
	{
		std::list<Widget *> Widget::s_widgets = std::list<Widget *>();

		Widget::Widget()
			:m_bVisible(true)
		{
			// TODO this is called before s_widgets is initialized because of other globals that need a widget
			s_widgets.push_back(this);
		}

		Widget::~Widget()
		{
			// TODO will the equality be ok?
			s_widgets.erase(std::find(s_widgets.begin(), s_widgets.end(), this));
		}

		

	}
}