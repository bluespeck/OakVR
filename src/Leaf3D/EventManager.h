
#ifndef __OAK3D_INCLUDE_LEAF3D_EVENTMANAGER_H__
#define __OAK3D_INCLUDE_LEAF3D_EVENTMANAGER_H__

#include <map>
#include <set>
#include <queue>

#include "Event.h"
#include "IListenForEvents.h"
#include "Core/Utils/Singleton.h"


namespace ro3d
{
	namespace Leaf3D
	{
		class EventManager : public ro3d::Core::Singleton<EventManager>
		{
		public:
			void RegisterListener(Event::EventType evType, IListenForEvents *pListener);
			void UnregisterListener(IListenForEvents *pListener);
			void AddEvent(Event *ev);
			void Update();
		private:
			void DispatchEvent(Event *ev);

			std::map<Event::EventType, std::set<IListenForEvents *> > m_listeners;
			std::queue<Event *> m_eventQueue;
		};
	}
}

#endif
