#include "AABB.h"


namespace maths {

	void AABB::SetMin(const glm::vec3& m)
	{
		m_min = m;
	}

	void AABB::SetMax(const glm::vec3& m)
	{
		m_max = m;
	}

}
