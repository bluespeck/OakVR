
#include "IToolTipped.h"

namespace ro3d
{
	namespace Leaf3D
	{
		IToolTipped::IToolTipped()
			:m_toolTipText(L"")
		{
			
		}

		void IToolTipped::SetToolTip(std::wstring text)
		{
			m_toolTipText = text;
		}

		std::wstring IToolTipped::GetToolTip()
		{
			return m_toolTipText;
		}
	}
}
