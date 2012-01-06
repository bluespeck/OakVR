
#include "Widget.h"

namespace Oak3D
{
	namespace Leaf3D
	{
		Widget::Widget()
			:m_bVisible(true)
		{
			s_widgets.push_back(std::shared_ptr<Widget>(this));
		}

		Widget::~Widget()
		{
			// TODO will the equality be ok?
			s_widgets.remove(std::shared_ptr<Widget>(this));
		}

		

	}
}