#include "CollisionComponent.h"

#include "Globals.h"
#include "graphics/objects/BaseObject.h"
#include "PhysicsComponent.h"


namespace components {

	CollisionComponent::CollisionComponent(graphics::BaseObject* owner):
		BaseComponent{ EComponentType::COLLISION, owner },
		physics::Collision{ }
	{
	}

	CollisionComponent::~CollisionComponent()
	{
	}

	void CollisionComponent::Update(float deltaTime)
	{
		if (!m_enabled) return;

		const physics::AABB& bbox = GetBoundingBox();
		std::vector<graphics::BaseObject*> objects = Globals::GetIntersectObjects(GetOwner());
		if (objects.empty()) return;
		// for test
		PhysicsComponent* physicsComponent = GetOwner()->GetComponent<PhysicsComponent>(EComponentType::PHYSICS_MECHANICS);
		if (physicsComponent) {
			physicsComponent->SetEnabled(false);
		}
	}

}
