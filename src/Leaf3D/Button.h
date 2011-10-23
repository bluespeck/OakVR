
#ifndef _OAK3D_LEAF3D_BUTTON_H_
#define _OAK3D_LEAF3D_BUTTON_H_

#include <wstring>
#include <functional>

#include "Clickable.h"
#include "Focusable.h"

namespace Oak3D
{
	namespace Leaf3D
	{
		class Button : public Focusable, public Clickable
		{
		public:
			Button();

		private:
			std::wstring m_text;	// TODO ?

		};
	}
}

#endif
