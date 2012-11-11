#ifndef __OAK3D_INCLUDE_LEAF3D_ITOOLTIPPED_H__
#define __OAK3D_INCLUDE_LEAF3D_ITOOLTIPPED_H__

#include <string>

namespace ro3d
{
	namespace Leaf3D
	{
		class IToolTipped
		{
		public:
			IToolTipped();

			void SetToolTip(std::wstring text);
			std::wstring GetToolTip();

		protected:
			std::wstring m_toolTipText;

		};
	}
}

#endif
