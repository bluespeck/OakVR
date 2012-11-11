
#ifndef __OAK3D_INCLUDE_LEAF3D_WIDGETCONTAINER_H__
#define __OAK3D_INCLUDE_LEAF3D_WIDGETCONTAINER_H__

#include <memory>
#include <list>

#include "Widget.h"

namespace ro3d
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
