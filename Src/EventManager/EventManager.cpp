#include "EventManager.h"

static IEventManager* g_pEventMgr = NULL;
GenericObjectFactory<IEventData, EventType> g_eventFactory;

IEventManager* IEventManager::Get(void)
{
	//GCC_ASSERT(g_pEventMgr);
	return g_pEventMgr;
}

IEventManager::IEventManager(const char* pName, bool setAsGlobal)
{
	if (setAsGlobal)
	{
		if (g_pEventMgr)
		{
			//GCC_ERROR("Attempting to create two global event managers! The old one will be destroyed and overwritten with this one.");
			delete g_pEventMgr;
		}

		g_pEventMgr = this;
	}
}

IEventManager::~IEventManager(void)
{
	if (g_pEventMgr == this)
		g_pEventMgr = NULL;
}

/////////////////////////////////////////////////////////////

EventManager::EventManager(const char* pName, bool setAsGlobal)
	: IEventManager(pName, setAsGlobal)
{
	m_activeQueue = 0;
}

EventManager::~EventManager()
{

}

bool EventManager::VAddListener(const EventListenerDelegate& eventDelegate, const EventType& type)
{
	//GCC_LOG("Events", "Attempting to add delegate function for event type: " + ToStr(type, 16));

	EventListenerList& eventListenerList = m_eventListeners[type];  // this will find or create the entry
	for (auto it = eventListenerList.begin(); it != eventListenerList.end(); ++it)
	{
		if (eventDelegate == (*it))
		{
			//GCC_WARNING("Attempting to double-register a delegate");
			return false;
		}
	}

	eventListenerList.push_back(eventDelegate);
	//GCC_LOG("Events", "Successfully added delegate for event type: " + ToStr(type, 16));

	return true;
}

bool EventManager::VRemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type)
{
	//GCC_LOG("Events", "Attempting to remove delegate function from event type: " + ToStr(type, 16));
	bool success = false;

	auto findIt = m_eventListeners.find(type);
	if (findIt != m_eventListeners.end())
	{
		EventListenerList& listeners = findIt->second;
		for (auto it = listeners.begin(); it != listeners.end(); ++it)
		{
			if (eventDelegate == (*it))
			{
				listeners.erase(it);
				//GCC_LOG("Events", "Successfully removed delegate function from event type: " + ToStr(type, 16));
				success = true;
				break;  // we don't need to continue because it should be impossible for the same delegate function to be registered for the same event more than once
			}
		}
	}

	return success;
}

bool EventManager::VTriggerEvent(const IEventDataPtr& pEvent) const
{
	//GCC_LOG("Events", "Attempting to trigger event " + std::string(pEvent->GetName()));
	bool processed = false;

	auto findIt = m_eventListeners.find(pEvent->VGetEventType());
	if (findIt != m_eventListeners.end())
	{
		const EventListenerList& eventListenerList = findIt->second;
		for (EventListenerList::const_iterator it = eventListenerList.begin(); it != eventListenerList.end(); ++it)
		{
			EventListenerDelegate listener = (*it);
			//GCC_LOG("Events", "Sending Event " + std::string(pEvent->GetName()) + " to delegate.");
			listener(pEvent);  // call the delegate
			processed = true;
		}
	}

	return processed;
}

bool EventManager::VQueueEvent(const IEventDataPtr& pEvent)
{
	//GCC_ASSERT(m_activeQueue >= 0);
	//GCC_ASSERT(m_activeQueue < EVENTMANAGER_NUM_QUEUES);

	// make sure the event is valid
	if (!pEvent)
	{
		//GCC_ERROR("Invalid event in VQueueEvent()");
		return false;
	}

	//GCC_LOG("Events", "Attempting to queue event: " + std::string(pEvent->GetName()));

	auto findIt = m_eventListeners.find(pEvent->VGetEventType());
	if (findIt != m_eventListeners.end())
	{
		m_queues[m_activeQueue].push_back(pEvent);
		//GCC_LOG("Events", "Successfully queued event: " + std::string(pEvent->GetName()));
		return true;
	}
	else
	{
		//GCC_LOG("Events", "Skipping event since there are no delegates registered to receive it: " + std::string(pEvent->GetName()));
		return false;
	}
}

bool EventManager::VAbortEvent(const EventType& inType, bool allOfType)
{
	//GCC_ASSERT(m_activeQueue >= 0);
	//GCC_ASSERT(m_activeQueue < EVENTMANAGER_NUM_QUEUES);

	bool success = false;
	EventListenerMap::iterator findIt = m_eventListeners.find(inType);

	if (findIt != m_eventListeners.end())
	{
		EventQueue& eventQueue = m_queues[m_activeQueue];
		auto it = eventQueue.begin();
		while (it != eventQueue.end())
		{
			// Removing an item from the queue will invalidate the iterator, so have it point to the next member.  All
			// work inside this loop will be done using thisIt.
			auto thisIt = it;
			++it;

			if ((*thisIt)->VGetEventType() == inType)
			{
				eventQueue.erase(thisIt);
				success = true;
				if (!allOfType)
					break;
			}
		}
	}

	return success;
}

bool EventManager::VUpdate(unsigned long maxMillis)
{
	unsigned long currMs = GetTickCount();
	unsigned long maxMs = ((maxMillis == IEventManager::kINFINITE) ? (IEventManager::kINFINITE) : (currMs + maxMillis));

	// swap active queues and clear the new queue after the swap
	int queueToProcess = m_activeQueue;
	m_activeQueue = (m_activeQueue + 1) % EVENTMANAGER_NUM_QUEUES;
	m_queues[m_activeQueue].clear();

	//GCC_LOG("EventLoop", "Processing Event Queue " + ToStr(queueToProcess) + "; " + ToStr((unsigned long)m_queues[queueToProcess].size()) + " events to process");

	// Process the queue
	while (!m_queues[queueToProcess].empty())
	{
		// pop the front of the queue
		IEventDataPtr pEvent = m_queues[queueToProcess].front();
		m_queues[queueToProcess].pop_front();
		//GCC_LOG("EventLoop", "\t\tProcessing Event " + std::string(pEvent->GetName()));

		const EventType& eventType = pEvent->VGetEventType();

		// find all the delegate functions registered for this event
		auto findIt = m_eventListeners.find(eventType);
		if (findIt != m_eventListeners.end())
		{
			const EventListenerList& eventListeners = findIt->second;
			//GCC_LOG("EventLoop", "\t\tFound " + ToStr((unsigned long)eventListeners.size()) + " delegates");

			// call each listener
			for (auto it = eventListeners.begin(); it != eventListeners.end(); ++it)
			{
				EventListenerDelegate listener = (*it);
				//GCC_LOG("EventLoop", "\t\tSending event " + std::string(pEvent->GetName()) + " to delegate");
				listener(pEvent);
			}
		}

		// check to see if time ran out
		currMs = GetTickCount();
		if (maxMillis != IEventManager::kINFINITE && currMs >= maxMs)
		{
			//GCC_LOG("EventLoop", "Aborting event processing; time ran out");
			break;
		}
	}

	// If we couldn't process all of the events, push the remaining events to the new active queue.
	// Note: To preserve sequencing, go back-to-front, inserting them at the head of the active queue
	bool queueFlushed = (m_queues[queueToProcess].empty());
	if (!queueFlushed)
	{
		while (!m_queues[queueToProcess].empty())
		{
			IEventDataPtr pEvent = m_queues[queueToProcess].back();
			m_queues[queueToProcess].pop_back();
			m_queues[m_activeQueue].push_front(pEvent);
		}
	}

	return queueFlushed;
}