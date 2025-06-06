#pragma once

#include "graphics/objects/BaseObject.h"


namespace graphics {
	class Coord;
}


namespace mesh {

	class Quad : public graphics::BaseObject {
	public:
		Quad();
		~Quad();

		virtual void Initialize() override;
		virtual void Render() override;

		void RefreshNormal();
		const glm::vec3& GetNormal() const { return m_normal; }

	private:
		glm::vec3 m_normal;

	};

}
