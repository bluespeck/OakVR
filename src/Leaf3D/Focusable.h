
#ifndef __OAK3D_INCLUDE_LEAF3D_FOCUSABLE_H__
#define __OAK3D_INCLUDE_LEAF3D_FOCUSABLE_H__

namespace Oak3D
{
	namespace Leaf3D
	{
		class Focusable
		{
		public:
			void SetFocus(bool focus);
			bool IsFocused();


		private:
			bool m_hasFocus;

		};
	}
}

#endif
