#include "Events.h"


namespace events {

	// BEGIN: BASE
	BaseEvent::BaseEvent(const EEventType& type) :
		m_type{ type }
	{
	}

	BaseEvent::~BaseEvent()
	{
	}
	// END: BASE

	// BEGIN: BUTTONS
	DeviceButtonEvent::DeviceButtonEvent(const EEventType& type, int key, int scanCode, int mods) :
		BaseEvent(type),
		m_key{ key },
		m_scanCode{ scanCode },
		m_mods{ mods }
	{
	}

	DeviceButtonEvent::~DeviceButtonEvent()
	{
	}
	// END: BUTTONS

	// BEGIN: MOUSE_MOVE
	MouseMoveEvent::MouseMoveEvent(const EEventType& type, float x, float y) :
		BaseEvent(type),
		m_x{ x },
		m_y{ y }
	{
	}

	MouseMoveEvent::~MouseMoveEvent()
	{
	}
	// END: MOUSE_MOVE

	// BEGIN: MOUSE_WHEEL
	MouseWheelEvent::MouseWheelEvent(const EEventType& type, float offsetX, float offsetY) :
		BaseEvent(type),
		m_x{ offsetX },
		m_y{ offsetY }
	{
	}

	MouseWheelEvent::~MouseWheelEvent()
	{
	}
	// END: MOUSE_WHEEL

}
