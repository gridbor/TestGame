#pragma once

#include <memory>
#include <unordered_map>
#include <string>

#include "graphics/objects/Updatable.h"
#include "graphics/scene/Scene.h"


namespace scene {

	class SceneManager : public Updatable {
	public:
		SceneManager();
		~SceneManager();

		void Initialize();
		void RestartScene(const std::string& sceneName);

		virtual void Update(float deltaTime) override;
		void SceneRender();
		void SceneRenderAlpha();

		Scene* GetCurrentScene() const { return m_currentScene; }

	private:
		void SetCurrentScene(Scene* scene);

	private:
		std::unordered_map<std::string, std::unique_ptr<Scene>> m_scenes;
		Scene* m_currentScene;

	};

}
