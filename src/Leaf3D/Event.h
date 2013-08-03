
#ifndef __OAKVR_INCLUDE_LEAF3D_EVENT_H__
#define __OAKVR_INCLUDE_LEAF3D_EVENT_H__

#include "Core/Utils/StringId.h"

namespace oakvr
{
	namespace Leaf3D
	{
		class Widget;

		class Event
		{
		public:
			typedef oakvr::Core::StringId EventType;
			typedef oakvr::Core::StringId EventSubtype;

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
