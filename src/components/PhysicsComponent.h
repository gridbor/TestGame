#pragma once

#include "physics/Mechanics.h"
#include "BaseComponent.h"


namespace components {

	class PhysicsComponent : public BaseComponent, public physics::Mechanics {
	public:
		PhysicsComponent();
		~PhysicsComponent();

		virtual void Update(float deltaTime) override;

	};

}
