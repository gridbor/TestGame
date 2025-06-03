#pragma once

#include <glm/glm.hpp>


namespace physics {

	class Mechanics {
	protected:
		Mechanics();

	public:
		virtual ~Mechanics();

	protected:
		void ApplyFreeFall(float deltaTime);

	protected:
		float m_mass;
		glm::vec3 m_velocity;
		glm::vec3 m_acceleration;
		glm::vec3 m_gravity;

	};

}
