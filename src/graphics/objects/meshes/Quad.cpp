#include "Quad.h"

#include "Globals.h"
#include "GameApp.h"
#include "tools/GameStorage.h"
#include "managers/ShadersManager.h"
#include "graphics/objects/helpers/Coord.h"


namespace mesh {

	Quad::Quad():
		m_normal{ }
	{
		LOG("Quad::constructor");
	}

	Quad::~Quad()
	{
		LOG("Quad::~destructor");
	}

	void Quad::Initialize()
	{
		m_vertices = {
			-0.25f, -0.25f,  0.f,    1.f, 0.f, 0.f, 1.f,
			 0.25f, -0.25f,  0.f,    0.f, 1.f, 0.f, 1.f,
			-0.25f,  0.25f,  0.f,    0.f, 0.f, 1.f, 1.f,
			 0.25f,  0.25f,  0.f,    0.f, 0.f, 0.f, 1.f
		};
		m_indices = { 0, 1, 2, 3 };
		m_stride = 7;
		m_elementsDrawMode = GL_TRIANGLE_STRIP;

		m_shader = Globals::GetShader("default");

		m_useTexture = false;

		BaseObject::Initialize();

		RefreshNormal();
	}

	void Quad::Render()
	{
		BaseObject::Render();
	}

	void Quad::RefreshNormal()
	{
		glm::vec3 v1 = glm::vec3(m_vertices[0], m_vertices[1], m_vertices[2]);
		glm::vec3 v2 = glm::vec3(m_vertices[7], m_vertices[8], m_vertices[9]);
		glm::vec3 v3 = glm::vec3(m_vertices[14], m_vertices[15], m_vertices[16]);
		m_normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));
	}

}
