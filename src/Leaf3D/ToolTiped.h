#ifndef __OAK3D_INCLUDE_LEAF3D_TOOLTIPED_H__
#define __OAK3D_INCLUDE_LEAF3D_TOOLTIPED_H__

#include <string>

namespace Oak3D
{
	namespace Leaf3D
	{
		class ToolTiped
		{
		public:
			ToolTiped();

			void SetToolTip(std::wstring text);
			std::wstring GetToolTip();

		protected:
			std::wstring m_toolTipText;

		};
	}
}

#endif
