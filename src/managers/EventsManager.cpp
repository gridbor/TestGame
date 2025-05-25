#include "EventsManager.h"

#include "events/EventListener.h"


EventsManager::EventsManager()
{
	LOG("EventsManager::constructor");
}

EventsManager::~EventsManager()
{
	LOG("EventsManager::~destructor");
}

void EventsManager::Update()
{
	if (!m_deleteListeners.empty()) {
		for (auto it = m_deleteListeners.begin(); it != m_deleteListeners.end(); ++it) {
			ListenerDeleter* deleter = it->get();
			if (deleter) {
				for (auto eIt = m_events.begin(); eIt != m_events.end();) {
					if (deleter->type == events::EEventType::NONE || (deleter->type != events::EEventType::NONE && deleter->type == eIt->first)) {
						for (auto sIt = eIt->second.begin(); sIt != eIt->second.end();) {
							if ((*sIt)->IsOwner(deleter->owner)) {
								sIt = eIt->second.erase(sIt);
							}
							else {
								++sIt;
							}
						}
					}
					if (eIt->second.empty()) {
						eIt = m_events.erase(eIt);
					}
					else {
						++eIt;
					}
				}
			}
		}
		m_deleteListeners.clear();
	}

	if (!m_addedListeners.empty()) {
		for (auto it = m_addedListeners.begin(); it != m_addedListeners.end(); ++it) {
			ListenerAdder* addListener = it->get();
			if (addListener) {
				bool exist = false;
				auto evIt = m_events.find(addListener->type);
				if (evIt != m_events.end()) {
					for (auto listenerIt = evIt->second.begin(); listenerIt != evIt->second.end(); ++listenerIt) {
						events::EventListener* eventListener = listenerIt->get();
						if (eventListener->IsSame(addListener->listener.get())) {
							exist = true;
							break;
						}
					}
				}
				if (!exist) {
					m_events[addListener->type].push_back(addListener->listener);
				}
			}
		}
		m_addedListeners.clear();
	}
}

void EventsManager::AddEventListener(const events::EEventType& type, void* owner, std::function<void(const events::BaseEvent&)> callback)
{
	bool exist = false;
	std::shared_ptr<events::EventListener> listener = std::make_shared<events::EventListener>(owner, callback);
	for (auto it = m_addedListeners.begin(); it != m_addedListeners.end(); ++it) {
		ListenerAdder* addListener = it->get();
		if (addListener && addListener->type == type && addListener->listener->IsSame(listener.get())) {
			exist = true;
			break;
		}
	}
	if (!exist) {
		m_addedListeners.push_back(std::make_shared<ListenerAdder>(type, listener));
	}
}

void EventsManager::RemoveEventListener(const events::EEventType& type, void* owner)
{
	bool exist = false;
	for (auto it = m_deleteListeners.begin(); it != m_deleteListeners.end(); ++it) {
		ListenerDeleter* delListener = it->get();
		if (delListener && delListener->owner == owner
			&& (delListener->type == type
				|| delListener->type == events::EEventType::NONE
				|| type == events::EEventType::NONE)) {
			if (type == events::EEventType::NONE) {
				delListener->type = type;
			}
			exist = true;
			break;
		}
	}
	if (!exist) {
		m_deleteListeners.push_back(std::make_shared<ListenerDeleter>(owner, type));
	}

	for (auto it = m_addedListeners.begin(); it != m_addedListeners.end();) {
		ListenerAdder* addListener = it->get();
		if (addListener && addListener->type == type && addListener->listener->IsOwner(owner)) {
			it = m_addedListeners.erase(it);
		}
		else {
			++it;
		}
	}
}

void EventsManager::RemoveEventListener(void* owner)
{
	RemoveEventListener(events::EEventType::NONE, owner);
}

void EventsManager::DispatchEvents(const events::BaseEvent& event)
{
	events::EEventType eventType = event.GetType();
	auto eventIt = m_events.find(eventType);
	if (eventIt != m_events.end()) {
		for (auto sIt = eventIt->second.begin(); sIt != eventIt->second.end(); ++sIt) {
			if (IsDeletedListener(eventType, (*sIt)->GetOwner())) continue;
			(*sIt)->Disptach(event);
		}
	}
}

bool EventsManager::IsDeletedListener(const events::EEventType& type, void* owner) const
{
	bool result = false;
	for (auto it = m_deleteListeners.begin(); it != m_deleteListeners.end(); ++it) {
		ListenerDeleter* delListener = it->get();
		if (delListener && delListener->owner == owner && (delListener->type == type || delListener->type == events::EEventType::NONE)) {
			result = true;
			break;
		}
	}
	return result;
}
