#include "Mechanics.h"


namespace physics {

	Mechanics::Mechanics():
		m_mass{ 1.f },
		m_velocity{ 0.f },
		m_acceleration{ 0.f },
		m_gravity{ worldGravity }
	{
	}

	Mechanics::~Mechanics()
	{
	}

}
