
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
			Label(std::string text = L"");
			void SetLabel(std::string text);
			std::string GetLabel();
		protected:
			std::string m_labelText;
		};
	}
}

#endif
