#ifndef __OAK3D_INCLUDE_LEAF3D_ILISTENFOREVENTS_H__
#define __OAK3D_INCLUDE_LEAF3D_ILISTENFOREVENTS_H__

#include "Event.h"

namespace ro3d
{
	namespace Leaf3D
	{
		class IListenForEvents
		{
		public:
			virtual ~IListenForEvents() { }

			// for internal use only
			virtual void DispatchByEventSubtype(Event *) {}

		protected:
			bool m_bIListenForEvents;
		};
	}
}

#endif
