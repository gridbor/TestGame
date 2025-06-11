#pragma once

#include <glm/glm.hpp>


namespace maths {

	class Plane {
	public:
		Plane() = default;
		~Plane() = default;

		Plane(const glm::vec3& n, float d = 0.f);

		const glm::vec3& GetNormal() const { return m_normal; }
		void SetNormal(const glm::vec3& n);

		float GetDistance() const { return m_distance; }
		void SetDistance(float d);

	protected:
		glm::vec3 m_normal{ 0.f, 1.f, 0.f };
		float m_distance{ 0.f };

	};

}
