
#include "Label.h"

namespace ro3d
{
	namespace Leaf3D
	{
		// --------------------------------------------------------------------------------
		Label::Label(std::wstring text /* = L"" */ )
			:m_labelText(text)
		{

		}

		// --------------------------------------------------------------------------------
		void Label::SetLabel(std::wstring text)
		{
			m_labelText = text;
		}

		// --------------------------------------------------------------------------------
		std::wstring Label::GetLabel()
		{
			return m_labelText;
		}
	}
}
