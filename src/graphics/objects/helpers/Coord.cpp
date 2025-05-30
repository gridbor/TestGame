#include "Coord.h"


namespace graphics {

	Coord::Coord():
		m_manualMatrixUpdate{ false }
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

		Renderable::Initialize();
	}

	void Coord::Render()
	{
		Renderable::Render();
	}

	void Coord::SetPosition(const glm::vec3& vec)
	{
		m_position = vec;
		if (!m_manualMatrixUpdate) UpdateMatrix();
	}

	void Coord::SetRotation(const glm::quat& rotation)
	{
		m_rotation = rotation;
		if (!m_manualMatrixUpdate) UpdateMatrix();
	}

	void Coord::SetScale(const glm::vec3& vec)
	{
		m_scale = vec;
		if (!m_manualMatrixUpdate) UpdateMatrix();
	}

	void Coord::UpdateMatrix()
	{
		glm::mat4 T = glm::translate(glm::mat4(1.f), m_position);
		glm::mat4 R = glm::mat4_cast(m_rotation);
		glm::mat4 S = glm::scale(glm::mat4(1.f), m_scale);
		m_matrix = T * R * S;
	}

}
