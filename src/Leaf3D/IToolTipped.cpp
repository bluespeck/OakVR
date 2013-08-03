
#include "IToolTipped.h"

namespace oakvr
{
	namespace Leaf3D
	{
		IToolTipped::IToolTipped()
			:m_toolTipText(L"")
		{
			
		}

		void IToolTipped::SetToolTip(std::string text)
		{
			m_toolTipText = text;
		}

		std::string IToolTipped::GetToolTip()
		{
			return m_toolTipText;
		}
	}
}
