#pragma once

#include <vector>
#include <memory>

#include "graphics/objects/Updatable.h"
#include "graphics/objects/BaseObject.h"


namespace scene {

	class Scene : public Updatable {
	public:
		Scene();
		~Scene();

		void Initialize();

		virtual void Update(float deltaTime) override;
		void Render();

		void SetRenderAlpha(bool alpha);

	private:
		bool m_renderAlpha;
		std::vector<std::shared_ptr<graphics::BaseObject>> m_objects;
		std::vector<graphics::BaseObject*> m_transparentObjects;
		std::vector<graphics::BaseObject*> m_opaqueObjects;

	};

}
