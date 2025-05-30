#pragma once

#include "graphics/objects/Renderable.h"
#include "graphics/objects/Transform.h"


namespace graphics {

	class Coord : public Renderable, public Transform {
	public:
		Coord();
		~Coord() = default;

		virtual void Initialize() override;
		virtual void Render() override;

		virtual void SetPosition(const glm::vec3& vec) override;
		virtual const glm::vec3& GetPosition() override { return m_position; }

		virtual void SetRotation(const glm::quat& rotation) override;
		virtual const glm::quat& GetRotation() override { return m_rotation; }

		virtual void SetScale(const glm::vec3& vec) override;
		virtual const glm::vec3& GetScale() override { return m_scale; }

	protected:
		void UpdateMatrix();

	protected:
		bool m_manualMatrixUpdate;

	};

}
