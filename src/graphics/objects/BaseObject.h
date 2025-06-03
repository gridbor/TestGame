#pragma once

#include <memory>

#include "Renderable.h"
#include "Updatable.h"
#include "Transform.h"
#include "helpers/Coord.h"
#include "components/BaseComponent.h"
#include "components/PhysicsComponent.h"
#include "components/CollisionComponent.h"


namespace graphics {

	enum class EMeshType : unsigned char {
		NONE = 0,
		QUAD,
		CUBE,
		SPHERE,
		CYLINDER,
		CAPSULE,
		CONE,
		PYRAMID,
		STATIC_MESH,
		SKELETAL_MESH,
		CAMERA
	};

	enum class EMovableType : unsigned char {
		STATIC = 0,
		DYNAMIC
	};

	class BaseObject : public Renderable, public Updatable, public Transform {
	protected:
		BaseObject(const EMeshType& meshType = EMeshType::NONE):
			m_movableType{ EMovableType::STATIC },
			m_meshType{ meshType },
			m_manualMatrixUpdate{ false },
			m_hasTransparency{ false },
			m_coordVisible{ true },
			m_worldUp{ 0.f, 1.f, 0.f },
			m_worldForward{ 0.f, 0.f, 1.f },
			m_forward{ 0.f, 0.f, 1.f },
			m_right{ 1.f, 0.f, 0.f },
			m_up{ 0.f, 1.f, 0.f },
			m_eulerAngles{ }
		{
			m_coord = std::make_unique<Coord>();
		}

	public:
		virtual ~BaseObject()
		{
			m_coord.reset();
			for (auto& component : m_components) {
				component.reset();
			}
			m_components.clear();
		}


		virtual void Initialize() override {
			if (m_coordVisible) m_coord->Initialize();
			Renderable::Initialize();
		}

		virtual void Render() override {
			if (m_coordVisible) m_coord->Render();
			Renderable::Render();
		}

		virtual void Update(float deltaTime) override {
			if (IsStatic() || !m_updateEnabled) return;

			for (const auto& component : m_components) {
				component->Update(deltaTime);
			}
		}


		const EMeshType& GetMeshType() const { return m_meshType; }


		bool IsStatic() const { return m_movableType == EMovableType::STATIC; }
		bool IsDynamic() const { return m_movableType == EMovableType::DYNAMIC; }

		void SetMovableType(const EMovableType& movableType) {
			if (m_movableType == movableType) return;
			m_movableType = movableType;
		}


		void AddComponent(const components::EComponentType& componentType) {
			switch (componentType) {
			case components::EComponentType::COLLISION:
				m_components.push_back(std::make_unique<components::CollisionComponent>(this));
				break;
			case components::EComponentType::PHYSICS_MECHANICS:
				m_components.push_back(std::make_unique<components::PhysicsComponent>(this));
				break;
			}
		}

		template<typename T>
		T* GetComponent(const components::EComponentType& componentType) const {
			for (auto it = m_components.begin(); it != m_components.end(); it++) {
				if ((*it)->GetType() == componentType) {
					return dynamic_cast<T*>(it->get());
				}
			}
			return nullptr;
		}

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
			m_eulerAngles.x = fmodf(pitch, glm::two_pi<float>());
		}
		virtual float GetPitch() const { return m_eulerAngles.x; }

		virtual void SetYaw(float yaw) {
			m_eulerAngles.y = fmodf(yaw, glm::two_pi<float>());
		}
		virtual float GetYaw() const { return m_eulerAngles.y; }

		virtual void SetRoll(float roll) {
			m_eulerAngles.z = fmodf(roll, glm::two_pi<float>());
		}
		virtual float GetRoll() const { return m_eulerAngles.z; }

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

			components::CollisionComponent* collision = GetComponent<components::CollisionComponent>(components::EComponentType::COLLISION);
			if (collision != nullptr) {
				collision->RefreshAABB(GetVertices(), m_matrix);
			}
		}

		virtual void CalculateVectors() {
			m_forward = m_rotation * m_worldForward;
			m_right = glm::normalize(glm::cross(m_forward, m_worldUp));
			m_up = glm::cross(m_right, m_forward);
		}

	protected:
		EMovableType m_movableType;
		bool m_manualMatrixUpdate;
		bool m_hasTransparency;
		bool m_coordVisible;
		glm::vec3 m_worldUp;
		glm::vec3 m_worldForward;
		glm::vec3 m_forward;
		glm::vec3 m_right;
		glm::vec3 m_up;
		std::unique_ptr<Coord> m_coord;
		std::vector<std::unique_ptr<components::BaseComponent>> m_components;

	private:
		EMeshType m_meshType;
		// in radians
		glm::vec3 m_eulerAngles;

	};

}
