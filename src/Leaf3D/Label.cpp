
#include "Label.h"

namespace oakvr
{
	namespace Leaf3D
	{
		// --------------------------------------------------------------------------------
		Label::Label(std::string text /* = L"" */ )
			:m_labelText(text)
		{

		}

		// --------------------------------------------------------------------------------
		void Label::SetLabel(std::string text)
		{
			m_labelText = text;
		}

		// --------------------------------------------------------------------------------
		std::string Label::GetLabel()
		{
			return m_labelText;
		}
	}
}
