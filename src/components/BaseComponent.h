#pragma once

#include <string>

#include "graphics/objects/Updatable.h"


namespace graphics {
	class BaseObject;
}


namespace components {

	enum class EComponentType : unsigned char {
		NONE = 0,
		PHYSICS_MECHANICS
	};

	class BaseComponent : public Updatable {
	protected:
		explicit BaseComponent(const EComponentType& type, graphics::BaseObject* owner):
			m_type{ type },
			m_owner{ owner }
		{ }

	public:
		virtual ~BaseComponent() = default;

		const EComponentType& GetType() const { return m_type; }
		const std::string& GetName() const { return m_name; }
		graphics::BaseObject* GetOwner() const { return m_owner; }

		virtual void Update(float deltaTime) override { }

	protected:
		std::string m_name = "BaseComponent";

	private:
		EComponentType m_type;
		graphics::BaseObject* m_owner;

	};

}
