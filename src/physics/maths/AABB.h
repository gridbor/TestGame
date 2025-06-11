#pragma once

#include <glm/glm.hpp>


namespace maths {

	class AABB {
	public:
		AABB() = default;
		~AABB() = default;

		const glm::vec3& GetMin() const { return m_min; }
		void SetMin(const glm::vec3& m);

		const glm::vec3& GetMax() const { return m_max; }
		void SetMax(const glm::vec3& m);

	protected:
		glm::vec3 m_min{};
		glm::vec3 m_max{};

	};

}
