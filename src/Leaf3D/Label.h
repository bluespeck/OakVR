
#ifndef _OAK3D_LEAF3D_LABEL_H_
#define _OAK3D_LEAF3D_LABEL_H_

#include <string>
#include "ToolTiped.h"


namespace Oak3D
{
	namespace Leaf3D
	{
		class Label : public ToolTiped
		{
		public:
			Label(std::wstring text = L"");
			void SetLabel(std::wstring text);
			std::wstring GetLabel();
		protected:
			std::wstring m_labelText;
		};
	}
}

#endif
