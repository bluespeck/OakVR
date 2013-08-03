
#ifndef __OAKVR_INCLUDE_LEAF3D_WIDGETCONTAINER_H__
#define __OAKVR_INCLUDE_LEAF3D_WIDGETCONTAINER_H__

#include <memory>
#include <list>

#include "Widget.h"

namespace oakvr
{
	namespace Leaf3D
	{
		class WidgetContainer
		{
		public:
			WidgetContainer();
			virtual ~WidgetContainer();
			
			void AddWidget(std::shared_ptr<Widget> &pWidget);

		private:
			std::list<std::shared_ptr<Widget>> m_widgets;
		};
	}
}

#endif
