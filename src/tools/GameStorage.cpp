#include "GameStorage.h"

#include "systems/TaskSystem.h"
#include "managers/ResourcesManager.h"
#include "managers/ShadersManager.h"
#include "managers/EventsManager.h"
#include "managers/CameraManager.h"
#include "managers/InputManager.h"
#include "managers/SceneManager.h"


GameStorage::GameStorage()
{
	m_taskSystem = std::make_unique<task::TaskSystem>();
	m_resources = std::make_unique<ResourcesManager>();
	m_events = std::make_unique<EventsManager>();
	m_shaders = std::make_unique<ShadersManager>();
	m_inputs = std::make_unique<InputManager>();
	m_camera = std::make_unique<CameraManager>();
	m_scenes = std::make_unique<scene::SceneManager>();
}

GameStorage::~GameStorage()
{
	m_scenes.reset();
	m_camera.reset();
	m_inputs.reset();
	m_shaders.reset();
	m_events.reset();
	m_resources.reset();
	m_taskSystem.reset();
}

void GameStorage::Initialize()
{
	m_shaders->Initialize();
	m_inputs->Initialize();
	m_camera->Initialize();
	m_scenes->Initialize();
}

void GameStorage::Clear()
{
	m_inputs->Clear();
}
