#pragma once

#include "BaseObject.h"


namespace graphics {

	class TestRect : public BaseObject {
	public:
		TestRect();
		~TestRect();

		void Initialize() override;
		void Render() override;

	};

}
