#pragma once

#include <string>

#include "graphics/objects/Updatable.h"


namespace components {

	enum class EComponentType : unsigned char {
		NONE = 0,
		PHYSICS_MECHANICS
	};

	class BaseComponent : public Updatable {
	protected:
		BaseComponent(const EComponentType& type):
			m_type{ type }
		{ }

	public:
		virtual ~BaseComponent() = default;

		const EComponentType& GetType() const { return m_type; }
		const std::string& GetName() const { return m_name; }

		virtual void Update(float deltaTime) override { }

	protected:
		std::string m_name = "BaseComponent";

	private:
		EComponentType m_type;

	};

}
