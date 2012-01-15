#include "EventManager.h"

namespace Oak3D
{
	namespace Leaf3D
	{
		// --------------------------------------------------------------------------------
		void EventManager::RegisterListener(Event::EventType evType, IListenForEvents *pListener)
		{
			m_listeners[evType].insert(pListener);
		}

		// --------------------------------------------------------------------------------
		void EventManager::UnregisterListener(IListenForEvents *pListener)
		{
			auto it = m_listeners.begin();
			while(it != m_listeners.end())
			{
				auto found = it->second.find(pListener);
				if(found != it->second.end())
					it->second.erase(found);
				++it;
			}
		}

		// --------------------------------------------------------------------------------
		void EventManager::AddEvent(Event *ev)
		{
			m_eventQueue.push(ev);
		}

		// --------------------------------------------------------------------------------
		void EventManager::DispatchEvent(Event *ev)
		{
			if(ev->GetEventType() == Event::EventType("MouseEvent"))
			{
				auto evListeners = m_listeners[ev->GetEventType()];
				auto it = evListeners.begin();
				while(it != evListeners.end())
				{
					(*it)->DispatchByEventSubtype(ev);
					++it;
				}
			}
		}

		// --------------------------------------------------------------------------------
		void EventManager::Update()
		{
			while(m_eventQueue.size() > 0)
			{
				DispatchEvent(m_eventQueue.front());
				delete m_eventQueue.front();
				m_eventQueue.pop();
			}
		}
	}
}
