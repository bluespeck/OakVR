#ifndef __OAKVR_INCLUDE_LEAF3D_ITOOLTIPPED_H__
#define __OAKVR_INCLUDE_LEAF3D_ITOOLTIPPED_H__

#include <string>

namespace oakvr
{
	namespace Leaf3D
	{
		class IToolTipped
		{
		public:
			IToolTipped();

			void SetToolTip(std::string text);
			std::string GetToolTip();

		protected:
			std::string m_toolTipText;

		};
	}
}

#endif
