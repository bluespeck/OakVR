
#ifndef __OAKVR_INCLUDE_LEAF3D_FOCUSABLE_H__
#define __OAKVR_INCLUDE_LEAF3D_FOCUSABLE_H__

#include "FocusZone.h"

namespace oakvr
{
	namespace Leaf3D
	{
		class IFocusable
		{
		public:
			IFocusable();

			virtual ~IFocusable();

			void SetFocus(bool focus);
			bool IsFocused();
			IFocusable *CaptureMouse();
			IFocusable *ReleaseMouse();
			bool HasCapturedMouse();

			virtual FocusZone GetFocusZone() = 0;

		protected:
			bool m_bHasFocus;
		};
	}
}

#endif
