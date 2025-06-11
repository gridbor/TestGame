#include "CollisionComponent.h"

#include <string>

#include "Globals.h"
#include "graphics/objects/BaseObject.h"
#include "PhysicsComponent.h"


namespace components {

	CollisionComponent::CollisionComponent(graphics::BaseObject* owner):
		BaseComponentType{ owner },
		physics::Collision{ }
	{
		m_name = "CollisionComponent";
	}

	CollisionComponent::~CollisionComponent()
	{
	}

	void CollisionComponent::Update(float deltaTime)
	{
		if (!m_enabled) return;

		std::vector<graphics::BaseObject*> objects = Globals::GetIntersectObjects(GetOwner());
		if (objects.empty()) return;

		PhysicsComponent* physicsComponent = GetOwner()->GetComponent<PhysicsComponent>();
		if (physicsComponent) {
			// test
			if (!physicsComponent->OnGround()) {
				float deltaY = m_boundingBox.GetMin().y - objects[0]->GetComponent<CollisionComponent>()->GetBoundingBox().GetMax().y;
				GetOwner()->SetPosition(GetOwner()->GetPosition() - glm::vec3(0.f, deltaY, 0.f));
			}
			physicsComponent->SetOnGround(true);
		}
	}

}
