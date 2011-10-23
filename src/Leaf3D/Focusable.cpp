
#include "Focusable.h"

namespace Oak3D
{
	namespace Leaf3D
	{
		void Focusable::SetFocus(bool focus)
		{
			m_hasFocus = focus;
		}

		bool Focusable::IsFocused()
		{
			return m_hasFocus;
		}
	}
}