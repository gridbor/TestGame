#pragma once

#include "../BaseObject.h"


namespace graphics {

	class Coord : public BaseObject {
	public:
		Coord();
		~Coord() = default;

		virtual void Initialize() override;
		virtual void Render() override;

		void UpdateData(const glm::vec3& f, const glm::vec3& s, const glm::vec3& u);

	};

}
