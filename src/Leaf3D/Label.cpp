
#include "Label.h"

namespace Oak3D
{
	namespace Leaf3D
	{
		Label::Label(std::wstring text /* = L"" */ )
			:m_labelText(text)
		{

		}

		void Label::SetLabel(std::wstring text)
		{
			m_labelText = text;
		}

		std::wstring Label::GetLabel()
		{
			return m_labelText;
		}
	}
}
