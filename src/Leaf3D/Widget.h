
#ifndef _OAK3D_LEAF3D_WIDGET_H_
#define _OAK3D_LEAF3D_WIDGET_H_

#include <cstdint>

#include "ScreenPosition.h"
#include "ScreenSize2D.h"

namespace Oak3D
{
	namespace Leaf3D
	{
		class Widget
		{
		public:
			Widget();
			virtual ~Widget();

			ScreenPosition GetPosition();
			void SetPosition(const ScreenPosition &position);

			ScreenSize2D GetSize();
			void SetSize(const ScreenSize2D &size);

			
		private:
			ScreenPosition m_position;
			ScreenSize2D m_size;
			uint32_t m_depth; // 0 is on top
		};
	}
}

#endif
