#pragma once

#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


struct GLFWwindow;

class GameStorage;


class GameApp {
public:
	GameApp(int w, int h, const std::string& title);
	~GameApp();

	void Initialize();
	void MainLoop();

	const GameStorage* GetGameStorage() const {
		return m_gameStorage.get();
	}

	void UpdateProjection();
	void UpdateProjection(float aFov, float aNear, float aFar);

	void ToggleWireMode();

	float GetDeltaTime() const { return m_deltaTime; }

	void Exit();

private:
	void InitGL();
	void UpdateGLViewport();

	void GameLoop();
	void Update(float deltaTime);
	void Render();

	static void OnResize(GLFWwindow* window, int w, int h);
	static void OnRefresh(GLFWwindow* window);
	static void OnMove(GLFWwindow* window, int x, int y);

	static void KeyHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseButtonHandler(GLFWwindow* window, int button, int action, int mods);
	static void MouseMoveHandler(GLFWwindow* window, double xpos, double ypos);
	static void MouseWheelHandler(GLFWwindow* window, double xoffset, double yoffset);

private:
	GLFWwindow* m_window;
	std::string m_title;
	int m_width;
	int m_height;
	float m_loopLastTime;
	float m_deltaTime;

	std::unique_ptr<GameStorage> m_gameStorage;

	float m_fov;
	float m_near;
	float m_far;
	glm::mat4 m_projectionMatrix;

	bool m_wireMode;

};
