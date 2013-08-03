#ifndef __OAKVR_INCLUDE_LEAF3D_ILISTENFOREVENTS_H__
#define __OAKVR_INCLUDE_LEAF3D_ILISTENFOREVENTS_H__

#include "Event.h"

namespace oakvr
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
