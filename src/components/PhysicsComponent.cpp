#include "PhysicsComponent.h"

#include "graphics/objects/BaseObject.h"


namespace components {

	PhysicsComponent::PhysicsComponent(graphics::BaseObject* owner):
		BaseComponent{ EComponentType::PHYSICS_MECHANICS, owner },
		physics::Mechanics{ },
		m_onGround{ false }
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

		if (m_onGround) {
			m_velocity.y = 0.f;
		}
		else {
			ApplyFreeFall(deltaTime);
		}
		
		owner->SetPosition(owner->GetPosition() + m_velocity * deltaTime);
	}

	void PhysicsComponent::SetOnGround(bool onGround)
	{
		if (m_onGround == onGround) return;
		m_onGround = onGround;
	}

}
