#include "Coord.h"


namespace graphics {

	Coord::Coord()
	{
		m_elementsDrawMode = GL_LINES;
	}

	void Coord::Initialize()
	{
		m_vertices = {
			0.f, 0.f, 0.f,  1.f, 1.f, 1.f, 1.f,
			1.f, 0.f, 0.f,  1.f, 0.f, 0.f, 1.f,
			0.f, 1.f, 0.f,  0.f, 1.f, 0.f, 1.f,
			0.f, 0.f, 1.f,  0.f, 0.f, 1.f, 1.f
		};
		m_indices = { 0, 1, 0, 2, 0, 3 };
		m_stride = 7;
		m_useTexture = false;

		m_shader = Globals::GetShader("default");

		BaseObject::Initialize();
	}

	void Coord::Render()
	{
		BaseObject::Render();
	}

	void Coord::UpdateData(const glm::vec3& f, const glm::vec3& s, const glm::vec3& u)
	{
	}

}
