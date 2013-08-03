
#ifndef __OAKVR_INCLUDE_LEAF3D_ILISTENFORMOUSEEVENTS_H__
#define __OAKVR_INCLUDE_LEAF3D_ILISTENFORMOUSEEVENTS_H__

#include "IListenForEvents.h"
#include "MouseEvent.h"

namespace oakvr
{
	namespace Leaf3D
	{
		class IListenForMouseEvents : public virtual IListenForEvents
		{
		public:
			IListenForMouseEvents();
			virtual ~IListenForMouseEvents();
			
			virtual void OnMouseLeftButtonDown(MouseEvent *) {}
			virtual void OnMouseMiddleButtonDown(MouseEvent *) {}
			virtual void OnMouseRightButtonDown(MouseEvent *) {}
			virtual void OnMouseLeftButtonUp(MouseEvent *) {}
			virtual void OnMouseMiddleButtonUp(MouseEvent *) {}
			virtual void OnMouseRightButtonUp(MouseEvent *) {}
			virtual void OnMouseLeftButtonHeld(MouseEvent *) {}
			virtual void OnMouseMiddleButtonHeld(MouseEvent *) {}
			virtual void OnMouseRightButtonHeld(MouseEvent *) {}
			virtual void OnMouseLeftButtonPressed(MouseEvent *) {}
			virtual void OnMouseMiddleButtonPressed(MouseEvent *){}
			virtual void OnMouseRightButtonPressed(MouseEvent *) {}
			virtual void OnMouseLeftButtonReleased(MouseEvent *) {}
			virtual void OnMouseMiddleButtonReleased(MouseEvent *) {}
			virtual void OnMouseRightButtonReleased(MouseEvent *) {}
			virtual void OnMouseMoved(MouseEvent *) {}
			virtual void OnMouseWheel(MouseEvent *) {}

			// for internal use
			void DispatchByEventSubtype(Event *ev);
		};
	}
}

#endif
