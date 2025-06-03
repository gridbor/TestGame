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

	void Mechanics::ApplyFreeFall(float deltaTime)
	{
		m_velocity += m_gravity * deltaTime;
	}

}
