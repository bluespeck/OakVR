
#include "MouseEvent.h"

namespace ro3d
{
	namespace Leaf3D
	{
		Event::EventSubtype MouseEvent::eventSubtypeLButtonDown = "MouseLButtonDown";
		Event::EventSubtype MouseEvent::eventSubtypeMButtonDown = "MouseMButtonDown";
		Event::EventSubtype MouseEvent::eventSubtypeRButtonDown = "MouseRButtonDown";
		Event::EventSubtype MouseEvent::eventSubtypeLButtonUp = "MouseLButtonUp";
		Event::EventSubtype MouseEvent::eventSubtypeMButtonUp = "MouseMButtonUp";
		Event::EventSubtype MouseEvent::eventSubtypeRButtonUp = "MouseRButtonUp";
		Event::EventSubtype MouseEvent::eventSubtypeLButtonHeld = "MouseLButtonHeld";
		Event::EventSubtype MouseEvent::eventSubtypeMButtonHeld = "MouseMButtonHeld";
		Event::EventSubtype MouseEvent::eventSubtypeRButtonHeld = "MouseRButtonHeld";
		Event::EventSubtype MouseEvent::eventSubtypeLButtonPressed = "MouseLButtonPressed";
		Event::EventSubtype MouseEvent::eventSubtypeMButtonPressed = "MouseMButtonPressed";
		Event::EventSubtype MouseEvent::eventSubtypeRButtonPressed = "MouseRButtonPressed";
		Event::EventSubtype MouseEvent::eventSubtypeLButtonReleased = "MouseLButtonReleased";
		Event::EventSubtype MouseEvent::eventSubtypeMButtonReleased = "MouseMButtonReleased";
		Event::EventSubtype MouseEvent::eventSubtypeRButtonReleased = "MouseRButtonReleased";
		Event::EventSubtype MouseEvent::eventSubtypeMouseMoved = "MouseMoved";
		Event::EventSubtype MouseEvent::eventSubtypeMouseWheel = "MouseWheel";

		// --------------------------------------------------------------------------------
		MouseEvent::MouseEvent()
		{
			m_eventType = EventType("MouseEvent");
		}
	}
}
