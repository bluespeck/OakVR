
#ifndef _OAK3D_LEAF3D_CLICKEVENT_H_
#define _OAK3D_LEAF3D_CLICKEVENT_H_

#include "Event.h"
#include "ScreenPosition.h"

namespace Oak3D
{
	namespace Leaf3D
	{
		class MouseEvent : public Event
		{
			MouseEvent(ScreenPosition mousePosition);

			ScreenPosition GetMousePos();


		protected:
			ScreenPosition m_mousePosition;
		};
	}
}

#endif
