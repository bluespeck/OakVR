#ifndef __OAK3D_INCLUDE_LEAF3D_ITOOLTIPPED_H__
#define __OAK3D_INCLUDE_LEAF3D_ITOOLTIPPED_H__

#include <string>

namespace ro3d
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
