#pragma once

#include "BaseObject.h"


namespace graphics {

	class Coord;

	class Camera : public BaseObject {
	public:
		Camera();
		~Camera();

		virtual void Initialize() override;
		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		virtual void SetPosition(const glm::vec3& vec) override;
		virtual void SetRotation(const glm::quat& rot) override;

		void UpdateViewMatrix();
		const glm::mat4& GetViewMatrix() const { return m_viewMatrix; }
		const glm::mat4& GetModelMatrix() const { return m_matrix; }

		bool MousePitchYawUpdate(float pitch, float yaw);

		bool IsMovable() const { return m_isMovable; }
		bool IsRenderDisabled() const { return m_isRenderDisabled; }
		void SetRenderDisabled(bool isDisable);

	protected:
		virtual void CalculateVectors() override;

	protected:
		std::pair<float, float> m_pitchLimits;
		glm::mat4 m_viewMatrix;

	private:
		bool m_isMovable;
		bool m_isRenderDisabled;

	};

}
