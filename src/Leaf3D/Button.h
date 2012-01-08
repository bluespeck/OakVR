
#ifndef _OAK3D_LEAF3D_BUTTON_H_
#define _OAK3D_LEAF3D_BUTTON_H_

#include <string>
#include <functional>

#include "Widget.h"
#include "Clickable.h"
#include "Focusable.h"

namespace Oak3D
{
	namespace Leaf3D
	{
		class Button : public Widget, public Focusable, public Clickable
		{
		public:
			Button();

		private:
			std::wstring m_text;	// TODO ?

		};
	}
}

#endif
