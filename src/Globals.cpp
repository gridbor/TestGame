#include "Globals.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "tools/Logger.h"
#include "GameApp.h"
#include "tools/GameStorage.h"
#include "systems/TaskSystem.h"
#include "managers/ResourcesManager.h"
#include "managers/ShadersManager.h"
#include "managers/EventsManager.h"
#include "managers/InputManager.h"
#include "managers/SceneManager.h"
#include "graphics/objects/Shader.h"
#include "datas/ImageData.h"
#include "events/Events.h"


Globals::Globals():
	m_logger{ nullptr },
	m_game{ nullptr }
{
	printf("Globals::constructor\n");
}

Globals::~Globals()
{
	m_game = nullptr;
	m_logger = nullptr;
	printf("Globals::~destructor\n");
}

const GameStorage* Globals::GetGS()
{
	GameApp* g = Get()->m_game;
	if (!g) throw std::runtime_error("Globals::GetGS global GameApp is not found!");
	const GameStorage* gs = g->GetGameStorage();
	if (!gs) throw std::runtime_error("Globals::GetGS global GameStorage is not found!");
	return gs;
}


std::string Globals::ReadTextFile(const std::string& path, bool dontSave)
{
	return GetManager<ResourcesManager>(EManagerType::RESOURCES)->ReadTextFile(path, dontSave);
}

void Globals::AsyncReadTextFile(const std::string& path, std::function<void(const std::string&)> callback)
{
	GetManager<ResourcesManager>(EManagerType::RESOURCES)->AsyncReadTextFile(path, callback);
}

const std::shared_ptr<graphics::Shader> Globals::GetShader(const std::string& shaderName)
{
	return GetManager<ShadersManager>(EManagerType::SHADERS)->GetShader(shaderName);
}

std::vector<std::shared_ptr<graphics::Shader>> Globals::GetAllShaders()
{
	return GetManager<ShadersManager>(EManagerType::SHADERS)->GetAllShaders();
}

ImageData* Globals::GetImageData(const std::string& imagePath)
{
	return GetManager<ResourcesManager>(EManagerType::RESOURCES)->LoadImage(imagePath);
}

void Globals::AsyncGetImageData(const std::string& imagePath, std::function<void(ImageData*)> callback)
{
	GetManager<ResourcesManager>(EManagerType::RESOURCES)->AsyncLoadImage(imagePath, callback);
}


void Globals::AddEventListener(const events::EEventType& type, void* owner, std::function<void(const events::BaseEvent&)> callback)
{
	GetManager<EventsManager>(EManagerType::EVENTS)->AddEventListener(type, owner, callback);
}
void Globals::RemoveEventListener(void* owner, const events::EEventType& type)
{
	GetManager<EventsManager>(EManagerType::EVENTS)->RemoveEventListener(type, owner);
}
void Globals::DispatchEvent(const events::BaseEvent& event)
{
	GetManager<EventsManager>(EManagerType::EVENTS)->DispatchEvents(event);
}

bool Globals::KeyIsPressed(int key, const EInputButtonType& type)
{
	return GetManager<InputManager>(EManagerType::INPUT)->IsPressed(key, type);
}

const MouseMove& Globals::MouseMoveDelta()
{
	return GetManager<InputManager>(EManagerType::INPUT)->GetMouseMoveDelta();
}

const MouseWheel& Globals::MouseWheelDelta()
{
	return GetManager<InputManager>(EManagerType::INPUT)->GetMouseWheelDelta();
}


float Globals::GetTime() { return glfwGetTime(); }

float Globals::GetDeltaTime()
{ 
	GameApp* g = Get()->GetGame();
	return g ? g->GetDeltaTime() : 0.0;
}

void Globals::ExitGame()
{
	GameApp* g = Get()->GetGame();
	if (g) g->Exit();
}


void Globals::SetLogger(Logger* ptr)
{
	if (!m_logger && ptr) {
		m_logger = ptr;
	}
}

void Globals::SetGame(GameApp* ptr)
{
	if (!m_game && ptr) {
		m_game = ptr;
	}
}
