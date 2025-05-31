#pragma once


namespace physics {

	class Mechanics {
	protected:
		Mechanics();

	public:
		virtual ~Mechanics();

	public:
		inline static float worldGravity = 9.80665f;

	protected:
		float m_mass;
		float m_velocity;
		float m_acceleration;
		float m_gravity;

	};

}
