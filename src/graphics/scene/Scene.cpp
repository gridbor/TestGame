#include "Scene.h"

#include "tools/Logger.h"
#include "graphics/objects/meshes/Quad.h"
#include "graphics/objects/meshes/Cube.h"
#include "components/PhysicsComponent.h"
#include "components/CollisionComponent.h"


namespace scene {

	Scene::Scene():
		m_renderAlpha{ false }
	{
		LOG("Scene::constructor");
	}

	Scene::~Scene()
	{
		m_transparentObjects.clear();
		m_opaqueObjects.clear();
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
		plane->AddComponent(components::EComponentType::COLLISION);
		plane->SetPosition(glm::vec3(0.f, -2.f, 0.f));
		plane->SetRotation(glm::quat(glm::vec3(-glm::half_pi<float>(), 0.f, 0.f)));
		plane->SetScale(glm::vec3(100.f, 100.f, 1.f));
		plane->RefreshNormal();
		std::shared_ptr<mesh::Cube> cube = std::make_shared<mesh::Cube>();
		cube->SetMovableType(graphics::EMovableType::DYNAMIC);
		cube->Initialize();
		cube->AddComponent(components::EComponentType::COLLISION);
		cube->AddComponent(components::EComponentType::PHYSICS_MECHANICS);
		cube->SetPosition(glm::vec3(0.f, 10.f, 0.f));
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

		for (const auto& obj : m_objects) {
			obj->Update(deltaTime);
		}
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

	std::vector<graphics::BaseObject*> Scene::GetIntersectObjects(graphics::BaseObject* target) const
	{
		if (target == nullptr) return {};

		components::CollisionComponent* collision = target->GetComponent<components::CollisionComponent>();
		if (collision == nullptr) return {};

		const auto& bbox = collision->GetBoundingBox();
		std::vector<graphics::BaseObject*> intersectObjects;
		for (const auto& object : m_objects) {
			if (object.get() == target) continue;
			components::CollisionComponent* otherCollision = object->GetComponent<components::CollisionComponent>();
			if (otherCollision) {
				const auto& other_bbox = otherCollision->GetBoundingBox();
				if (bbox.max.x < other_bbox.min.x || bbox.min.x > other_bbox.max.x) continue;
				if (bbox.max.y < other_bbox.min.y || bbox.min.y > other_bbox.max.y) continue;
				if (bbox.max.z < other_bbox.min.z || bbox.min.z > other_bbox.max.z) continue;
				intersectObjects.push_back(object.get());
			}
		}
		return intersectObjects;
	}

}
