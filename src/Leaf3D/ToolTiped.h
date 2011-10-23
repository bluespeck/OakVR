#ifndef _OAK3D_LEAF3D_TOOLTIPED_H_
#define _OAK3D_LEAF3D_TOOLTIPED_H_

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
