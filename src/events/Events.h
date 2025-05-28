#pragma once

#include "tools/Logger.h"


namespace events {

	enum class EEventType : char {
		NONE = 0,
		KEY_DOWN,
		KEY_REPEAT,
		KEY_UP,
		MOUSE_DOWN,
		MOUSE_UP,
		MOUSE_WHEEL,
		MOUSE_MOVE,
		CUSTOM
	};


	class BaseEvent {
	protected:
		BaseEvent(const EEventType& type);

	public:
		virtual ~BaseEvent();

		const EEventType& GetType() const { return m_type; }

	protected:
		EEventType m_type;

	};


	// BEGIN: BUTTONS
	class DeviceButtonEvent : public BaseEvent {
	public:
		DeviceButtonEvent(const EEventType& type, int key, int scanCode, int mods);
		~DeviceButtonEvent();

		int GetKey() const { return m_key; }
		int GetScanCode() const { return m_scanCode; }
		int GetMods() const { return m_mods; }

	private:
		int m_key;
		int m_scanCode;
		int m_mods;

	};
	// END: BUTTONS


	// BEGIN: MOUSE
	class MouseMoveEvent : public BaseEvent {
	public:
		MouseMoveEvent(const EEventType& type, float x, float y);
		~MouseMoveEvent();

		float GetX() const { return m_x; }
		float GetY() const { return m_y; }

	private:
		float m_x;
		float m_y;

	};

	class MouseWheelEvent : public BaseEvent {
	public:
		MouseWheelEvent(const EEventType& type, float offsetX, float offsetY);
		~MouseWheelEvent();

		float GetX() const { return m_x; }
		float GetY() const { return m_y; }

	private:
		float m_x;
		float m_y;

	};
	// END: MOUSE


	// BEGIN: CUSTOM
	class CustomEvent : public BaseEvent {
	public:
		CustomEvent(const EEventType& type, const std::string& eventName);
		~CustomEvent();

		const std::string& GetName() const { return m_eventName; }

	private:
		std::string m_eventName;

	};
	// END: CUSTOM

}
