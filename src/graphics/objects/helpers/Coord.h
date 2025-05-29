#pragma once

#include "../BaseObject.h"


namespace graphics {

	class Coord : public BaseObject {
	public:
		Coord();
		~Coord() = default;

		virtual void Initialize() override;
		virtual void Render() override;

	};

}
