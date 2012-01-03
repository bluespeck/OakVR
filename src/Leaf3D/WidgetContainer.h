
#ifndef _OAK3D_LEAF3D_WIDGETCONTAINER_H_
#define _OAK3D_LEAF3D_WIDGETCONTAINER_H_

#include <memory>
#include <list>

#include "Widget.h"

namespace Oak3D
{
	namespace Leaf3D
	{
		class WidgetContainer
		{
		public:
			WidgetContainer();
			virtual ~WidgetContainer();
			
			void AddWidget(std::shared_ptr<Widget> *pWidget);

		private:
			std::list<std::shared_ptr<Widget>> m_widgets;
		};
	}
}

#endif
