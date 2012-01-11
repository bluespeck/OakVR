
#include <algorithm>

#include "Widget.h"


namespace Oak3D
{
	namespace Leaf3D
	{
		// HACK this will leak eventually, but the executable will cleanup at exit
		std::list<Widget *> *Widget::s_widgets = nullptr;

		Widget::Widget()
			:m_bVisible(true)
		{
			if( s_widgets == nullptr )
				s_widgets = new std::list<Widget *>();
			
			s_widgets->push_back(this);
		}

		Widget::~Widget()
		{
			// TODO will the equality be ok?
			s_widgets->erase(std::find(s_widgets->begin(), s_widgets->end(), this));

		}

		bool Widget::WidgetsAvailable()
		{
			return s_widgets != nullptr && s_widgets->size() > 0;
		}

	}
}