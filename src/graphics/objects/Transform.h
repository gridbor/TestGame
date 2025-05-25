#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace graphics {

	class Transform {
	public:
		Transform() = default;
		virtual ~Transform() = default;

		virtual void SetPosition(const glm::vec3& vec) = 0;
		virtual const glm::vec3& GetPosition() = 0;

		virtual void SetRotation(const glm::quat& rotation) = 0;
		virtual const glm::quat& GetRotation() = 0;

		virtual void SetScale(const glm::vec3& vec) = 0;
		virtual const glm::vec3& GetScale() = 0;

	protected:
		glm::vec3 m_position = glm::vec3{};
		glm::quat m_rotation = glm::quat{};
		glm::vec3 m_scale = glm::vec3{ 1.f };

	};

}
