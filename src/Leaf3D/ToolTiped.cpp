
#include "ToolTiped.h"

namespace Oak3D
{
	namespace Leaf3D
	{
		ToolTiped::ToolTiped()
			:m_toolTipText(L"")
		{
			
		}

		void ToolTiped::SetToolTip(std::wstring text)
		{
			m_toolTipText = text;
		}

		std::wstring ToolTiped::GetToolTip()
		{
			return m_toolTipText;
		}
	}
}
