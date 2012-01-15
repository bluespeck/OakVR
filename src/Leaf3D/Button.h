
#ifndef __OAK3D_INCLUDE_LEAF3D_BUTTON_H__
#define __OAK3D_INCLUDE_LEAF3D_BUTTON_H__

#include <string>
#include <functional>

#include "Widget.h"
#include "Clickable.h"
#include "Focusable.h"
#include "IListenForMouseEvents.h"

namespace Oak3D
{
	namespace Leaf3D
	{
		class Button : public Widget, public Focusable, public Clickable, public IListenForMouseEvents
		{
		public:
			Button();

			virtual void OnMouseMoved(MouseEvent *mev);

		private:
			std::wstring m_text;	// TODO ?

		};
	}
}

#endif
