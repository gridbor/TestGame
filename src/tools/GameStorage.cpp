#include "GameStorage.h"

#include "managers/ResourcesManager.h"
#include "managers/ShadersManager.h"
#include "managers/EventsManager.h"
#include "managers/CameraManager.h"
#include "managers/InputManager.h"


GameStorage::GameStorage()
{
	m_resources = std::make_unique<ResourcesManager>();
	m_shaders = std::make_unique<ShadersManager>();
	m_events = std::make_unique<EventsManager>();
	m_inputs = std::make_unique<InputManager>();
	m_camera = std::make_unique<CameraManager>();
}

GameStorage::~GameStorage()
{
	m_camera.reset();
	m_inputs.reset();
	m_events.reset();
	m_shaders.reset();
	m_resources.reset();
}

void GameStorage::Initialize()
{
	m_shaders->Initialize();
	m_inputs->Initialize();
	m_camera->Initialize();
}

void GameStorage::Clear()
{
	m_inputs->Clear();
}
