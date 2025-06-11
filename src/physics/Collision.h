#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "maths/AABB.h"
#include "maths/Plane.h"


namespace physics {

	class Collision {
	protected:
		Collision();

	public:
		virtual ~Collision();

		void RefreshAABB(const std::vector<glm::vec3>& vertices, const glm::mat4& modelMatrix);
		const maths::AABB& GetBoundingBox() const { return m_boundingBox; }

	protected:
		maths::AABB m_boundingBox;
		maths::Plane m_plane;

	};

}
