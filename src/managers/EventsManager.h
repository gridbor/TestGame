#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>

#include "events/Events.h"


namespace events {
	class EventListener;
}


struct ListenerAdder {
	events::EEventType type;
	std::shared_ptr<events::EventListener> listener;

	ListenerAdder(const events::EEventType& aType, std::shared_ptr<events::EventListener> aListener):
		type{ aType },
		listener{ aListener }
	{
		LOG("ListenerAdder::constructor");
	}
	~ListenerAdder()
	{
		LOG("ListenerAdder::~destructor");
		listener.reset();
	}
};

struct ListenerDeleter {
	events::EEventType type;
	void* owner;

	ListenerDeleter(void* aOwner, const events::EEventType& aType = events::EEventType::NONE):
		type{ aType },
		owner{ aOwner }
	{
		LOG("ListenerDeleter::constructor");
	}
	~ListenerDeleter()
	{
		LOG("ListenerDeleter::~destructor");
		owner = nullptr;
	}
};


class EventsManager {
public:
	EventsManager();
	~EventsManager();

	void Update();

	void AddEventListener(const events::EEventType& type, void* owner, std::function<void(const events::BaseEvent&)> callback);
	void RemoveEventListener(const events::EEventType& type, void* owner);
	void RemoveEventListener(void* owner);
	void DispatchEvents(const events::BaseEvent& event);

private:
	bool IsDeletedListener(const events::EEventType& type, void* owner) const;

private:
	std::unordered_map<events::EEventType, std::vector<std::shared_ptr<events::EventListener>>> m_events;
	std::vector<std::shared_ptr<ListenerAdder>> m_addedListeners;
	std::vector<std::shared_ptr<ListenerDeleter>> m_deleteListeners;

};
