#pragma once

#include "physics/Mechanics.h"
#include "BaseComponent.h"


namespace graphics {
	class BaseObject;
}


namespace components {

	class PhysicsComponent : public BaseComponentType<EComponentType::PHYSICS_MECHANICS>, public physics::Mechanics{
	public:
		PhysicsComponent(graphics::BaseObject* owner);
		~PhysicsComponent();

		virtual void Update(float deltaTime) override;

		bool OnGround() const { return m_onGround; }
		void SetOnGround(bool onGround);

	private:
		bool m_onGround;

	};

}
