#pragma once

#include <functional>

#include "Events.h"


namespace events {

	class EventListener {
	public:
		EventListener(void* owner, std::function<void(const BaseEvent&)> callback);
		~EventListener();

		void* GetOwner() const { return m_owner; }
		bool IsOwner(void* owner) const;
		bool IsSame(EventListener* other) const;
		void Disptach(const BaseEvent& event);

	private:
		void* m_owner;
		std::function<void(const BaseEvent&)> m_callback;

	};

}
