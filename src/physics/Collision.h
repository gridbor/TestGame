#pragma once

#include <vector>
#include <glm/glm.hpp>


namespace physics {

	struct AABB {
		glm::vec3 min{};
		glm::vec3 max{};
	};

	class Collision {
	protected:
		Collision();

	public:
		virtual ~Collision();

		void RefreshAABB(const std::vector<glm::vec3>& vertices, const glm::mat4& modelMatrix);
		const AABB& GetBoundingBox() const { return m_boundingBox; }

	protected:
		AABB m_boundingBox;

	};

}
