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
