
#ifndef _OAK3D_LEAF3D_EVENT_H_
#define _OAK3D_LEAF3D_EVENT_H_

namespace Oak3D
{
	namespace Leaf3D
	{
		class Widget;

		class Event
		{
		public:
			Event(Widget *source);
		protected:
			Widget *m_source;
		};
	}
}

#endif
