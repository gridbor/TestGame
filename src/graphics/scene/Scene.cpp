#include "Scene.h"

#include "tools/Logger.h"
#include "graphics/objects/meshes/Quad.h"
#include "graphics/objects/meshes/Cube.h"


namespace scene {

	Scene::Scene():
		m_renderAlpha{ false }
	{
		LOG("Scene::constructor");
	}

	Scene::~Scene()
	{
		for (auto& obj : m_objects) {
			obj.reset();
		}
		m_objects.clear();
		LOG("Scene::~destructor");
	}

	void Scene::Initialize()
	{
		std::shared_ptr<mesh::Quad> plane = std::make_shared<mesh::Quad>();
		plane->Initialize();
		plane->SetPosition(glm::vec3(0.f, -2.f, 0.f));
		plane->SetRotation(glm::quat(glm::vec3(-glm::half_pi<float>(), 0.f, 0.f)));
		plane->SetScale(glm::vec3(100.f, 100.f, 1.f));
		std::shared_ptr<mesh::Cube> cube = std::make_shared<mesh::Cube>();
		cube->Initialize();
		m_objects.push_back(plane);
		m_objects.push_back(cube);

		for (const auto& obj : m_objects) {
			if (obj->IsTransparent()) {
				m_transparentObjects.push_back(obj.get());
			}
			else {
				m_opaqueObjects.push_back(obj.get());
			}
		}
	}

	void Scene::Update(float deltaTime)
	{
		if (!m_updateEnabled) return;
	}

	void Scene::Render()
	{
		const auto& objects = m_renderAlpha ? m_transparentObjects : m_opaqueObjects;
		for (const auto& obj : objects) {
			obj->Render();
		}
	}

	void Scene::SetRenderAlpha(bool alpha)
	{
		if (m_renderAlpha == alpha) return;
		m_renderAlpha = alpha;
	}

}
