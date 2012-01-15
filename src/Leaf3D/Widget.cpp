
#include <algorithm>

#include "Widget.h"


namespace Oak3D
{
	namespace Leaf3D
	{
		std::list<Widget *> *Widget::s_widgets = nullptr;
		bool Widget::s_bDeleteListIfEmpty = false;

		// --------------------------------------------------------------------------------
		Widget::Widget()
			:m_bVisible(true)
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
	}
}