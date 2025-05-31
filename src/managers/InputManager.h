#pragma once

#include <memory>
#include <vector>
#include <unordered_map>


enum class EInputButtonType : unsigned char {
	NONE = 0,
	KEYBOARD,
	MOUSE
};

struct InputButton {
	int keyCode;
	float createdTime;

	InputButton(int key, float time):
		keyCode{ key },
		createdTime{ time }
	{ }
};

struct MouseMove {
	float x;
	float y;
};

struct MouseWheel {
	float offsetX;
	float offsetY;
};

struct InputMouse {
	MouseMove move;
	MouseWheel wheel;
	MouseMove previousPos;
	bool firstTime;

	InputMouse()
	{
		firstTime = true;
		previousPos.x = 0.0;
		previousPos.y = 0.0;
		Reset();
	}

	void Reset()
	{
		move.x = 0.0;
		move.y = 0.0;
		wheel.offsetX = 0.0;
		wheel.offsetY = 0.0;
	}
	void SetMove(float x, float y)
	{
		move.x = x;
		move.y = y;
	}
	void SetWheel(float x, float y)
	{
		wheel.offsetX = x;
		wheel.offsetY = y;
	}
	void SetPreviousPos(float x, float y)
	{
		previousPos.x = x;
		previousPos.y = y;
	}
};


namespace events {
	class BaseEvent;
}


class InputManager {
public:
	InputManager();
	~InputManager();

	void Initialize();
	void Clear();

	bool IsPressed(int key, const EInputButtonType& type) const;
	const MouseMove& GetMouseMoveDelta() const { return m_inputMouse.move; };
	const MouseWheel& GetMouseWheelDelta() const { return m_inputMouse.wheel; };
	void ResetMouseInputs();

private:
	void ButtonsHandler(const events::BaseEvent& event);
	void MouseMoveHandler(const events::BaseEvent& event);
	void MouseWheelHandler(const events::BaseEvent& event);

	void SetInputButton(int keyCode, std::vector<InputButton>& vec, bool add);

private:
	std::unordered_map<EInputButtonType, std::vector<InputButton>> m_buttons;
	InputMouse m_inputMouse;

};
