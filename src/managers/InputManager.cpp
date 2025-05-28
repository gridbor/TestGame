#include "InputManager.h"

#include <GLFW/glfw3.h>

#include "Globals.h"
#include "GameApp.h"
#include "events/Events.h"


InputManager::InputManager():
	m_inputMouse{}
{
	m_buttons[EInputButtonType::KEYBOARD] = std::vector<InputButton>();
	m_buttons[EInputButtonType::MOUSE] = std::vector<InputButton>();
}

InputManager::~InputManager()
{
	m_buttons.clear();
}

void InputManager::Initialize()
{
	Globals::AddEventListener(events::EEventType::KEY_DOWN, this, std::bind(&InputManager::ButtonsHandler, this, std::placeholders::_1));
	Globals::AddEventListener(events::EEventType::KEY_UP, this, std::bind(&InputManager::ButtonsHandler, this, std::placeholders::_1));
	Globals::AddEventListener(events::EEventType::MOUSE_DOWN, this, std::bind(&InputManager::ButtonsHandler, this, std::placeholders::_1));
	Globals::AddEventListener(events::EEventType::MOUSE_UP, this, std::bind(&InputManager::ButtonsHandler, this, std::placeholders::_1));
	Globals::AddEventListener(events::EEventType::MOUSE_MOVE, this, std::bind(&InputManager::MouseMoveHandler, this, std::placeholders::_1));
	Globals::AddEventListener(events::EEventType::MOUSE_WHEEL, this, std::bind(&InputManager::MouseWheelHandler, this, std::placeholders::_1));
}

void InputManager::Clear()
{
	Globals::RemoveEventListener(this);
}

bool InputManager::IsPressed(int key, const EInputButtonType& type) const
{
	const std::vector<InputButton>& vec = m_buttons.at(type);
	auto it = std::find_if(vec.begin(), vec.end(),
		[key](const InputButton& value) { return value.keyCode == key; }
	);
	return it != vec.end();
}

void InputManager::ResetMouseInputs()
{
	m_inputMouse.Reset();
}

void InputManager::ButtonsHandler(const events::BaseEvent& event)
{
	events::DeviceButtonEvent buttonEvent = static_cast<const events::DeviceButtonEvent&>(event);
	const events::EEventType& type = buttonEvent.GetType();
	int key = buttonEvent.GetKey();
	switch (type) {
	case events::EEventType::KEY_DOWN:
		SetInputButton(key, m_buttons[EInputButtonType::KEYBOARD], true);
		break;
	case events::EEventType::KEY_UP:
		SetInputButton(key, m_buttons[EInputButtonType::KEYBOARD], false);
		break;
	case events::EEventType::MOUSE_DOWN:
		SetInputButton(key, m_buttons[EInputButtonType::MOUSE], true);
		break;
	case events::EEventType::MOUSE_UP:
		SetInputButton(key, m_buttons[EInputButtonType::MOUSE], false);
		break;
	}
	if (type == events::EEventType::KEY_DOWN) {
		switch (key) {
		case GLFW_KEY_ESCAPE: Globals::ExitGame(); break;
		case GLFW_KEY_F2: Globals::Get()->GetGame()->ToggleWireMode(); break;
		}
	}
}

void InputManager::MouseMoveHandler(const events::BaseEvent& event)
{
	events::MouseMoveEvent moveEvent = static_cast<const events::MouseMoveEvent&>(event);
	if (moveEvent.GetType() == events::EEventType::MOUSE_MOVE) {
		if (m_inputMouse.firstTime) {
			m_inputMouse.SetPreviousPos(moveEvent.GetX(), moveEvent.GetY());
			m_inputMouse.firstTime = false;
		}
		double x = moveEvent.GetX() - m_inputMouse.previousPos.x;
		double y = moveEvent.GetY() - m_inputMouse.previousPos.y;
		m_inputMouse.SetMove(x, y);
		m_inputMouse.SetPreviousPos(moveEvent.GetX(), moveEvent.GetY());
	}
}

void InputManager::MouseWheelHandler(const events::BaseEvent& event)
{
	events::MouseWheelEvent wheelEvent = static_cast<const events::MouseWheelEvent&>(event);
	if (wheelEvent.GetType() == events::EEventType::MOUSE_WHEEL) {
		m_inputMouse.SetWheel(wheelEvent.GetX(), wheelEvent.GetY());
	}
}

void InputManager::SetInputButton(int keyCode, std::vector<InputButton>& vec, bool add)
{
	auto it = std::find_if(vec.begin(), vec.end(),
		[keyCode](const InputButton& v) { return v.keyCode == keyCode; }
	);
	if (add && it == vec.end()) {
		vec.emplace_back(keyCode, Globals::GetTime());
	}
	else if (!add && it != vec.end()) {
		vec.erase(it);
	}
}
