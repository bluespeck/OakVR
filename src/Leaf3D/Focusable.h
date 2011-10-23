
#ifndef _OAK3D_LEAF3D_FOCUSABLE_H_
#define _OAK3D_LEAF3D_FOCUSABLE_H_

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
