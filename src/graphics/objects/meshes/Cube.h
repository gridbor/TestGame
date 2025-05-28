#pragma once

#include "graphics/objects/BaseObject.h"


namespace mesh {

	class Cube : public graphics::BaseObject {
	public:
		Cube();
		~Cube();

		virtual void Initialize() override;
		virtual void Update(float deltaTime) override;
		virtual void Render() override;

	private:

	};

}
