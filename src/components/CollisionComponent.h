#pragma once

#include "physics/Collision.h"
#include "BaseComponent.h"


namespace graphics {
	class BaseObject;
}


namespace components {

	class CollisionComponent : public BaseComponent, public physics::Collision {
	public:
		CollisionComponent(graphics::BaseObject* owner);
		~CollisionComponent();

		virtual void Update(float deltaTime) override;

	};

}
