#include "CollisionComponent.h"

#include "graphics/objects/BaseObject.h"


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
	}

}
