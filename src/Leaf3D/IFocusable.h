
#ifndef __OAK3D_INCLUDE_LEAF3D_FOCUSABLE_H__
#define __OAK3D_INCLUDE_LEAF3D_FOCUSABLE_H__

#include "FocusZone.h"

namespace ro3d
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
