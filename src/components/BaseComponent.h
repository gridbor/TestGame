#pragma once

#include <string>

#include "graphics/objects/Updatable.h"


namespace graphics {
	class BaseObject;
}


namespace components {

	enum class EComponentType : unsigned char {
		NONE = 0,
		COLLISION,
		PHYSICS_MECHANICS
	};

	class BaseComponent : public Updatable {
	protected:
		explicit BaseComponent(graphics::BaseObject* owner):
			m_owner{ owner },
			m_enabled{ true }
		{ }

	public:
		virtual ~BaseComponent() = default;

		virtual const EComponentType GetType() const = 0;
		const std::string& GetName() const { return m_name; }
		graphics::BaseObject* GetOwner() const { return m_owner; }

		virtual void Update(float deltaTime) override { }

		virtual void SetEnabled(bool enable) {
			if (m_enabled == enable) return;
			m_enabled = enable;
		}
		virtual bool IsEnabled() const { return m_enabled; }

	protected:
		std::string m_name = "BaseComponent";
		bool m_enabled;

	private:
		graphics::BaseObject* m_owner;

	};


	template <EComponentType componentType>
	class BaseComponentType : public BaseComponent {
	protected:
		BaseComponentType(graphics::BaseObject* owner):
			BaseComponent{ owner }
		{ }

	public:
		const EComponentType GetType() const override { return componentType; }
		static constexpr EComponentType s_type = componentType;

	};

}
