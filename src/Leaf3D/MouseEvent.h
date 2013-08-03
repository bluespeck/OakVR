
#ifndef __OAKVR_INCLUDE_LEAF3D_CLICKEVENT_H__
#define __OAKVR_INCLUDE_LEAF3D_CLICKEVENT_H__

#include "Event.h"
#include "ScreenPosition.h"

namespace oakvr
{
	namespace Leaf3D
	{
		class MouseEvent : public Event
		{
		public:
			MouseEvent();

			ScreenPosition2D GetMousePos();

			static EventSubtype eventSubtypeLButtonDown;
			static EventSubtype eventSubtypeMButtonDown;
			static EventSubtype eventSubtypeRButtonDown;
			static EventSubtype eventSubtypeLButtonUp;
			static EventSubtype eventSubtypeMButtonUp;
			static EventSubtype eventSubtypeRButtonUp;
			static EventSubtype eventSubtypeLButtonHeld;
			static EventSubtype eventSubtypeMButtonHeld;
			static EventSubtype eventSubtypeRButtonHeld;
			static EventSubtype eventSubtypeLButtonPressed;
			static EventSubtype eventSubtypeMButtonPressed;
			static EventSubtype eventSubtypeRButtonPressed;
			static EventSubtype eventSubtypeLButtonReleased;
			static EventSubtype eventSubtypeMButtonReleased;
			static EventSubtype eventSubtypeRButtonReleased;
			static EventSubtype eventSubtypeMouseMoved;
			static EventSubtype eventSubtypeMouseWheel;

			struct MouseData
			{
				bool m_bLButtonDown;
				bool m_bMButtonDown;
				bool m_bRButtonDown;
				int32_t m_wheelDelta;
				ScreenPosition2D m_mousePosition;
			} m_mouseData;
		};
	}
}

#endif
