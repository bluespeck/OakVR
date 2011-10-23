
#include "Widget.h"

namespace Oak3D
{
	namespace Leaf3D
	{
		Widget::~Widget()
		{

		}

		ScreenPosition Widget::GetPosition()
		{
			return m_position;
		}

		void Widget::SetPosition(const ScreenPosition &position)
		{
			m_position = position;
		}

		ScreenSize2D Widget::GetSize()
		{
			return m_size;
		}

		void Widget::SetSize(const ScreenSize2D &size)
		{
			m_size = size;
		}
	}
}