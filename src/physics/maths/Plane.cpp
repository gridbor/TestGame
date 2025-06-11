#include "Plane.h"


namespace maths {

	Plane::Plane(const glm::vec3& n, float d):
		m_normal{ n },
		m_distance{ d }
	{
	}

	void Plane::SetNormal(const glm::vec3& n)
	{
		m_normal = n;
	}

	void Plane::SetDistance(float d)
	{
		m_distance = d;
	}

}
