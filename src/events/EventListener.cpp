#include "EventListener.h"


namespace events {

	EventListener::EventListener(void* owner, std::function<void(const BaseEvent&)> callback):
		m_owner{ owner },
		m_callback{ callback }
	{
	}

	EventListener::~EventListener()
	{
		m_owner = nullptr;
		m_callback = nullptr;
	}

	bool EventListener::IsOwner(void* owner) const
	{
		return m_owner == owner;
	}

	bool EventListener::IsSame(EventListener* other) const
	{
		bool result = false;
		if (m_owner == other->m_owner
			&& std::strcmp(
				m_callback.target_type().name(),
				other->m_callback.target_type().name()
			) == 0) {
			result = true;
		}
		return result;
	}

	void EventListener::Disptach(const BaseEvent& event)
	{
		if (m_callback) m_callback(event);
	}

}
