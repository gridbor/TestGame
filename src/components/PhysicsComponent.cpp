#include "PhysicsComponent.h"

#include "graphics/objects/BaseObject.h"


namespace components {

	PhysicsComponent::PhysicsComponent(graphics::BaseObject* owner):
		BaseComponent{ EComponentType::PHYSICS_MECHANICS, owner },
		physics::Mechanics{ }
	{
		m_name = "PhysicsComponent";
	}

	PhysicsComponent::~PhysicsComponent()
	{
	}

	void PhysicsComponent::Update(float deltaTime)
	{
		if (!m_enabled) return;

		BaseComponent::Update(deltaTime);

		graphics::BaseObject* owner = GetOwner();
		if (owner == nullptr) return;
		owner->SetPosition(FreeFall(deltaTime, owner->GetPosition()));
	}

}
