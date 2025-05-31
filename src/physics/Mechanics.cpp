#include "Mechanics.h"


namespace physics {

	Mechanics::Mechanics():
		m_mass{ 1.f },
		m_velocity{ 0.f },
		m_acceleration{ 0.f },
		m_gravity{ 0.f, -9.81f, 0.f }
	{
	}

	Mechanics::~Mechanics()
	{
	}

	glm::vec3 Mechanics::FreeFall(float deltaTime, const glm::vec3& position)
	{
		m_velocity += m_gravity * deltaTime;
		return position + m_velocity * deltaTime;
	}

}
