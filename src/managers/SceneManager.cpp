#include "SceneManager.h"

#include "tools/Logger.h"


namespace scene {

	SceneManager::SceneManager():
		m_currentScene{ nullptr }
	{
		LOG("SceneManager::constructor");
	}

	SceneManager::~SceneManager()
	{
		m_currentScene = nullptr;
		for (auto& [_, value] : m_scenes) {
			value.reset();
		}
		m_scenes.clear();
		LOG("SceneManager::~destructor");
	}

	void SceneManager::Initialize()
	{
		m_scenes["main"] = std::make_unique<Scene>();
		m_scenes["main"]->Initialize();

		SetCurrentScene(m_scenes["main"].get());
	}

	void SceneManager::RestartScene(const std::string& sceneName)
	{
		auto it = m_scenes.find(sceneName);
		if (it != m_scenes.end()) {
			bool isCurrentScene = m_scenes[sceneName].get() == m_currentScene;
			if (isCurrentScene) {
				m_currentScene = nullptr;
			}

			m_scenes[sceneName].reset();

			m_scenes[sceneName] = std::make_unique<Scene>();
			m_scenes[sceneName]->Initialize();

			if (isCurrentScene) {
				SetCurrentScene(m_scenes[sceneName].get());
			}
		}
	}

	void SceneManager::Update(float deltaTime)
	{
		if (!m_updateEnabled) return;

		if (m_currentScene)
			m_currentScene->Update(deltaTime);
	}

	void SceneManager::SceneRender()
	{
		if (m_currentScene) {
			m_currentScene->SetRenderAlpha(false);
			m_currentScene->Render();
		}
	}

	void SceneManager::SceneRenderAlpha()
	{
		if (m_currentScene) {
			m_currentScene->SetRenderAlpha(true);
			m_currentScene->Render();
		}
	}

	void SceneManager::SetCurrentScene(Scene* scene)
	{
		if (m_currentScene == scene || scene == nullptr) return;
		m_currentScene = scene;
	}

}
