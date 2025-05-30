#pragma once

#include <memory>

#include "Renderable.h"
#include "Updatable.h"
#include "Transform.h"
#include "helpers/Coord.h"


namespace graphics {

	class BaseObject : public Renderable, public Updatable, public Transform {
	protected:
		BaseObject() :
			m_manualMatrixUpdate{ false },
			m_hasTransparency{ false },
			m_coordVisible{ true },
			m_worldUp{ 0.f, 1.f, 0.f },
			m_worldForward{ 0.f, 0.f, 1.f },
			m_forward{ 0.f, 0.f, 1.f },
			m_right{ 1.f, 0.f, 0.f },
			m_up{ 0.f, 1.f, 0.f },
			m_pitch{ 0.f },
			m_yaw{ 0.f },
			m_roll{ 0.f }
		{
			m_coord = std::make_unique<Coord>();
		}

	public:
		virtual ~BaseObject()
		{
			m_coord.reset();
		}

		virtual void Initialize() override {
			if (m_coordVisible) m_coord->Initialize();
			Renderable::Initialize();
		}
		virtual void Render() override {
			if (m_coordVisible) m_coord->Render();
			Renderable::Render();
		}

		virtual void Update(float deltaTime) override { }

		// TRANSLATE
		virtual void SetPosition(const glm::vec3& vec) override {
			if (m_coordVisible) m_coord->SetPosition(vec);
			m_position = vec;
			if (!m_manualMatrixUpdate) UpdateMatrix();
		}
		virtual const glm::vec3& GetPosition() override { return m_position; }

		// ROTATE
		virtual void SetRotation(const glm::quat& rotation) override {
			if (m_coordVisible) m_coord->SetRotation(rotation);
			m_rotation = rotation;
			if (!m_manualMatrixUpdate) UpdateMatrix();
		}
		virtual const glm::quat& GetRotation() override { return m_rotation; }

		virtual void SetPitch(float pitch) {
			m_pitch = fmodf(pitch, glm::two_pi<float>());
		}
		virtual float GetPitch() const { return m_pitch; }

		virtual void SetYaw(float yaw) {
			m_yaw = fmodf(yaw, glm::two_pi<float>());
		}
		virtual float GetYaw() const { return m_yaw; }

		virtual void SetRoll(float roll) {
			m_roll = fmodf(roll, glm::two_pi<float>());
		}
		virtual float GetRoll() const { return m_roll; }

		// SCALE
		virtual void SetScale(const glm::vec3& vec) override {
			m_scale = vec;
			if (!m_manualMatrixUpdate) UpdateMatrix();
		}
		virtual const glm::vec3& GetScale() override { return m_scale; }

		// Direction Vectors
		const glm::vec3& GetForward() const { return m_forward; }
		const glm::vec3& GetRight() const { return m_right; }
		const glm::vec3& GetUp() const { return m_up; }

		bool IsTransparent() const { return m_hasTransparency; }

	protected:
		virtual void UpdateMatrix() {
			glm::mat4 T = glm::translate(glm::mat4(1.f), m_position);
			glm::mat4 R = glm::mat4_cast(m_rotation);
			glm::mat4 S = glm::scale(glm::mat4(1.f), m_scale);
			m_matrix = T * R * S;
		}

		virtual void CalculateVectors() {
			m_forward = m_rotation * m_worldForward;
			m_right = glm::normalize(glm::cross(m_forward, m_worldUp));
			m_up = glm::cross(m_right, m_forward);
		}

	protected:
		bool m_manualMatrixUpdate;
		bool m_hasTransparency;
		bool m_coordVisible;
		glm::vec3 m_worldUp;
		glm::vec3 m_worldForward;
		glm::vec3 m_forward;
		glm::vec3 m_right;
		glm::vec3 m_up;
		std::unique_ptr<Coord> m_coord;

	private:
		// in radians
		float m_pitch;
		float m_yaw;
		float m_roll;

	};
}
