#include "GameApp.h"

#ifndef GLAD_GL_IMPLEMENTATION
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#endif
#undef GLAD_GL_IMPLEMENTATION
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "tools/Logger.h"
#include "tools/GameStorage.h"
#include "systems/TaskSystem.h"
#include "managers/ResourcesManager.h"
#include "managers/ShadersManager.h"
#include "managers/EventsManager.h"
#include "managers/CameraManager.h"
#include "managers/InputManager.h"
#include "graphics/objects/TestRect.h"
#include "events/Events.h"


void APIENTRY OpenGLDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const char* message, const void* userParam)
{
	if (id == 131185 || id == 131204) return;
	LOG("OpenGL Debug Message (%d): %s\n----------------", id, message);
}


GameApp::GameApp(int w, int h, const std::string& title) :
	m_window{ nullptr },
	m_width{ w }, m_height{ h },
	m_title{ title },
	m_loopLastTime{ 0 },
	m_gameStorage{ nullptr },
	m_testRect{ nullptr },
	m_fov{ 45.f }, m_near{ 0.1f }, m_far{ 100.f },
	m_projectionMatrix{},
	m_deltaTime{ 0.f }
{
	LOG("GameApp::constructor\n");
}

void GameApp::Initialize()
{
	if (!glfwInit()) {
		throw std::runtime_error("GLFW Init Failed!\n");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
	if (!m_window) {
		glfwTerminate();
		throw std::runtime_error("GLFW Window Create Failed!\n");
	}

	glfwMakeContextCurrent(m_window);
	gladLoadGL(glfwGetProcAddress);

	glfwSetWindowUserPointer(m_window, reinterpret_cast<void*>(this));

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetWindowSizeCallback(m_window, OnResize);
	glfwSetWindowRefreshCallback(m_window, OnRefresh);
	glfwSetWindowPosCallback(m_window, OnMove);

	glfwSetKeyCallback(m_window, KeyHandler);
	glfwSetMouseButtonCallback(m_window, MouseButtonHandler);
	glfwSetCursorPosCallback(m_window, MouseMoveHandler);
	glfwSetScrollCallback(m_window, MouseWheelHandler);

	m_loopLastTime = glfwGetTime();

	m_gameStorage = std::make_unique<GameStorage>();
	m_gameStorage->Initialize();

	InitGL();
}

GameApp::~GameApp()
{
	if (m_testRect) m_testRect.reset();
	m_gameStorage->Clear();
	m_gameStorage.reset();
	LOG("--- WORKING TIME: %f", glfwGetTime());

	glfwDestroyWindow(m_window);
	glfwTerminate();
	LOG("GameApp::~destructor\n");
}

void GameApp::MainLoop()
{
	while (!glfwWindowShouldClose(m_window)) {
		GameLoop();
		glfwPollEvents();
	}
}

void GameApp::UpdateProjection()
{
	float aspect = (float)m_width / (float)m_height;
	m_projectionMatrix = glm::perspective(glm::radians(m_fov), aspect, m_near, m_far);

	auto shaders = Globals::GetAllShaders();
	for (auto& shader : shaders) {
		shader->SetUniform("u_projection", m_projectionMatrix);
	}
}

void GameApp::UpdateProjection(float aFov, float aNear, float aFar)
{
	m_fov = aFov;
	m_near = aNear;
	m_far = aFar;
	UpdateProjection();
}

void GameApp::Exit()
{
	if (m_window) {
		glfwSetWindowShouldClose(m_window, GLFW_TRUE);
	}
}

void GameApp::InitGL()
{
	int flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}

	UpdateGLViewport();
	glClearColor(0.25f, 0.25f, 0.25f, 1.f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	UpdateProjection();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	m_testRect = std::make_unique<graphics::TestRect>();
	m_testRect->Initialize();
}

void GameApp::UpdateGLViewport()
{
	glViewport(0, 0, m_width, m_height);
}

static unsigned int frame_count = 0;
void GameApp::GameLoop()
{
	double currentTime = glfwGetTime();
	m_deltaTime = currentTime - m_loopLastTime;
	m_loopLastTime = currentTime;

	Update(m_deltaTime);
	Render();

	frame_count++;
	if (frame_count > 100) {
		glfwSetWindowShouldClose(m_window, GLFW_TRUE);
	}
}

void GameApp::Update(float deltaTime)
{
	Globals::GetSystem<task::TaskSystem>(ESystemType::TASK)->Update();

	Globals::GetManager<EventsManager>(EManagerType::EVENTS)->Update();
	Globals::GetManager<CameraManager>(EManagerType::CAMERA)->Update(deltaTime);

	Globals::GetManager<InputManager>(EManagerType::INPUT)->ResetMouseInputs();
}

void GameApp::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// TODO: rendering objects sorting with transparent and opaque, for blending transparent sort from back to front

	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	if (m_testRect) {
		m_testRect->SetPosition(glm::vec3(0.f, 0.f, 0.f));
		m_testRect->SetScale(glm::vec3(2.f, 2.f, 2.f));
		m_testRect->Render();
	}

	Globals::GetManager<CameraManager>(EManagerType::CAMERA)->Render();
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);

	glfwSwapBuffers(m_window);
}

void GameApp::OnResize(GLFWwindow* window, int w, int h)
{
	GameApp* gameApp = reinterpret_cast<GameApp*>(glfwGetWindowUserPointer(window));
	if (gameApp) {
		gameApp->m_width = w;
		gameApp->m_height = h;
		gameApp->UpdateGLViewport();
	}
}

void GameApp::OnRefresh(GLFWwindow* window)
{
	GameApp* gameApp = reinterpret_cast<GameApp*>(glfwGetWindowUserPointer(window));
	if (gameApp) {
		gameApp->GameLoop();
	}
}

void GameApp::OnMove(GLFWwindow* window, int x, int y)
{
	GameApp* gameApp = reinterpret_cast<GameApp*>(glfwGetWindowUserPointer(window));
	if (gameApp) {
		gameApp->GameLoop();
	}
}

void GameApp::KeyHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	events::DeviceButtonEvent* buttonEvent = nullptr;
	switch (action) {
	case GLFW_RELEASE:
		buttonEvent = new events::DeviceButtonEvent(events::EEventType::KEY_UP, key, scancode, mods);
		break;
	case GLFW_PRESS:
		buttonEvent = new events::DeviceButtonEvent(events::EEventType::KEY_DOWN, key, scancode, mods);
		break;
	case GLFW_REPEAT:
		buttonEvent = new events::DeviceButtonEvent(events::EEventType::KEY_REPEAT, key, scancode, mods);
		break;
	}
	if (buttonEvent) {
		Globals::DispatchEvent(*buttonEvent);
		delete buttonEvent;
	}
	buttonEvent = nullptr;
}

void GameApp::MouseButtonHandler(GLFWwindow* window, int button, int action, int mods)
{
	events::DeviceButtonEvent* buttonEvent = nullptr;
	switch (action) {
	case GLFW_RELEASE:
		buttonEvent = new events::DeviceButtonEvent(events::EEventType::MOUSE_UP, button, 0, mods);
		break;
	case GLFW_PRESS:
		buttonEvent = new events::DeviceButtonEvent(events::EEventType::MOUSE_DOWN, button, 0, mods);
		break;
	}
	if (buttonEvent) {
		Globals::DispatchEvent(*buttonEvent);
		delete buttonEvent;
	}
	buttonEvent = nullptr;
}

void GameApp::MouseMoveHandler(GLFWwindow* window, double xpos, double ypos)
{
	events::MouseMoveEvent* moveEvent = new events::MouseMoveEvent(events::EEventType::MOUSE_MOVE, xpos, ypos);
	if (moveEvent) {
		Globals::DispatchEvent(*moveEvent);
		delete moveEvent;
	}
	moveEvent = nullptr;
}

void GameApp::MouseWheelHandler(GLFWwindow* window, double xoffset, double yoffset)
{
	events::MouseWheelEvent* wheelEvent = new events::MouseWheelEvent(events::EEventType::MOUSE_WHEEL, xoffset, yoffset);
	if (wheelEvent) {
		Globals::DispatchEvent(*wheelEvent);
		delete wheelEvent;
	}
	wheelEvent = nullptr;
}
