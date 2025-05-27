#pragma once

#include <memory>

namespace task {
	class TaskSystem;
}
class ResourcesManager;
class ShadersManager;
class EventsManager;
class InputManager;
class CameraManager;


class GameStorage {
public:
	GameStorage();
	~GameStorage();

	void Initialize();
	void Clear();

	task::TaskSystem* GetTaskSystem() const { return m_taskSystem.get(); }
	ResourcesManager* GetResourcesManager() const { return m_resources.get(); }
	ShadersManager* GetShadersManager() const { return m_shaders.get(); }
	EventsManager* GetEventsManager() const { return m_events.get(); }
	InputManager* GetInputManager() const { return m_inputs.get(); }
	CameraManager* GetCameraManager() const { return m_camera.get(); }

private:
	std::unique_ptr<task::TaskSystem> m_taskSystem;
	std::unique_ptr<ResourcesManager> m_resources;
	std::unique_ptr<ShadersManager> m_shaders;
	std::unique_ptr<EventsManager> m_events;
	std::unique_ptr<InputManager> m_inputs;
	std::unique_ptr<CameraManager> m_camera;

};
