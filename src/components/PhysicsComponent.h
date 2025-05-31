#pragma once

#include "physics/Mechanics.h"
#include "BaseComponent.h"


namespace graphics {
	class BaseObject;
}


namespace components {

	class PhysicsComponent : public BaseComponent, public physics::Mechanics {
	public:
		PhysicsComponent(graphics::BaseObject* owner);
		~PhysicsComponent();

		virtual void Update(float deltaTime) override;

	};

}
