#pragma once

#include <vector>
#include <glm/glm.hpp>


namespace physics {

	struct AABB {
		glm::vec3 min{};
		glm::vec3 max{};
	};

	struct Plane {
		glm::vec3 normal{ 0.f, 1.f, 0.f };
		float distance = 0.f;
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
		Plane m_plane;

	};

}
