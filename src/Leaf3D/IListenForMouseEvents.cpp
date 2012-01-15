#include <cassert>
#include "IListenForMouseEvents.h"
#include "EventManager.h"

#include "MouseEvent.h"

namespace Oak3D
{
	namespace Leaf3D
	{
		// --------------------------------------------------------------------------------
		IListenForMouseEvents::IListenForMouseEvents()
		{
			Oak3D::Leaf3D::EventManager::GetInstance()->RegisterListener(Event::EventType("MouseEvent"), this);
		}

		IListenForMouseEvents::~IListenForMouseEvents()
		{
			Oak3D::Leaf3D::EventManager::GetInstance()->UnregisterListener(this);
		}

		// --------------------------------------------------------------------------------
		void IListenForMouseEvents::DispatchByEventSubtype(Event *ev)
		{
			assert(ev->GetEventType() == Event::EventType("MouseEvent"));
			MouseEvent *mev = (MouseEvent *)ev;
			
			const Event::EventSubtype est = mev->GetEventSubtype();

			if(est == mev->eventSubtypeLButtonDown)
				this->OnMouseLeftButtonDown(mev);
			else if(est == mev->eventSubtypeLButtonHeld)
				this->OnMouseLeftButtonHeld(mev);
			else if(est == mev->eventSubtypeLButtonUp)
				this->OnMouseLeftButtonUp(mev);
			else if(est == mev->eventSubtypeLButtonPressed)
				this->OnMouseLeftButtonPressed(mev);
			else if(est == mev->eventSubtypeLButtonReleased)
				this->OnMouseLeftButtonReleased(mev);

			else if(est == mev->eventSubtypeMButtonDown)
				this->OnMouseMiddleButtonDown(mev);
			else if(est == mev->eventSubtypeMButtonHeld)
				this->OnMouseMiddleButtonHeld(mev);
			else if(est == mev->eventSubtypeMButtonUp)
				this->OnMouseMiddleButtonUp(mev);
			else if(est == mev->eventSubtypeMButtonPressed)
				this->OnMouseMiddleButtonPressed(mev);
			else if(est == mev->eventSubtypeMButtonReleased)
				this->OnMouseMiddleButtonReleased(mev);

			else if(est == mev->eventSubtypeRButtonDown)
				this->OnMouseRightButtonDown(mev);
			else if(est == mev->eventSubtypeRButtonHeld)
				this->OnMouseRightButtonHeld(mev);
			else if(est == mev->eventSubtypeRButtonUp)
				this->OnMouseRightButtonUp(mev);
			else if(est == mev->eventSubtypeRButtonPressed)
				this->OnMouseRightButtonPressed(mev);
			else if(est == mev->eventSubtypeRButtonReleased)
				this->OnMouseRightButtonReleased(mev);

			else if(est == mev->eventSubtypeMouseMoved)
				this->OnMouseMoved(mev);
			else if(est == mev->eventSubtypeMouseWheel)
				this->OnMouseWheel(mev);
			
		}
	}
}
