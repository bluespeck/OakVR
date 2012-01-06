#include "WidgetContainer.h"

namespace Oak3D
{
	namespace Leaf3D
	{
		WidgetContainer::WidgetContainer()
		{

		}

		WidgetContainer::~WidgetContainer()
		{

		}

		void WidgetContainer::AddWidget(std::shared_ptr<Widget> &pWidget)
		{
			m_widgets.push_back(pWidget);
		}
	}
}