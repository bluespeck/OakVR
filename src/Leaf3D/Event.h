
#ifndef __OAK3D_INCLUDE_LEAF3D_EVENT_H__
#define __OAK3D_INCLUDE_LEAF3D_EVENT_H__

#include "Core/Utils/StringID.h"

namespace ro3d
{
	namespace Leaf3D
	{
		class Widget;

		class Event
		{
		public:
			typedef ro3d::Core::StringId EventType;
			typedef ro3d::Core::StringId EventSubtype;

			Event(): m_eventType("BaseEvent"), m_eventSubtype("None") {}
			virtual ~Event() {}

			const EventType &GetEventType() { return m_eventType; }
			const EventSubtype &GetEventSubtype() { return m_eventSubtype; }
			void SetEventSubType(const EventSubtype &evSubtype) { m_eventSubtype = evSubtype; }

		protected:
			EventType m_eventType;
			EventSubtype m_eventSubtype;

		};
	}
}

#endif
