#include "PhysicsComponent.h"


namespace components {

	PhysicsComponent::PhysicsComponent():
		BaseComponent{ EComponentType::PHYSICS_MECHANICS },
		physics::Mechanics{ }
	{
		m_name = "PhysicsComponent";
	}

	PhysicsComponent::~PhysicsComponent()
	{
	}

	void PhysicsComponent::Update(float deltaTime)
	{
		BaseComponent::Update(deltaTime);
	}

}
