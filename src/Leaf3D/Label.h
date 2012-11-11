
#ifndef __OAK3D_INCLUDE_LEAF3D_LABEL_H__
#define __OAK3D_INCLUDE_LEAF3D_LABEL_H__

#include <string>

#include "Widget.h"
#include "IToolTipped.h"


namespace ro3d
{
	namespace Leaf3D
	{
		class Label : public Widget, public IToolTipped
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
