#include "Cube.h"


namespace mesh {

	Cube::Cube()
	{
		LOG("Cube::constructor");
	}

	Cube::~Cube()
	{
		LOG("Cube::~destructor");
	}

	void Cube::Initialize()
	{
		m_vertices = {
			-0.5f, -0.5f,  0.5f,  1.f, 0.f, 0.f, 1.f,
			 0.5f, -0.5f,  0.5f,  0.f, 1.f, 0.f, 1.f,
			-0.5f,  0.5f,  0.5f,  0.f, 0.f, 1.f, 1.f,
			 0.5f,  0.5f,  0.5f,  1.f, 1.f, 1.f, 1.f,

			-0.5f, -0.5f, -0.5f,  1.f, 1.f, 0.f, 1.f,
			 0.5f, -0.5f, -0.5f,  1.f, 0.f, 1.f, 1.f,
			-0.5f,  0.5f, -0.5f,  0.f, 1.f, 1.f, 1.f,
			 0.5f,  0.5f, -0.5f,  0.f, 0.f, 0.f, 1.f,
		};
		m_indices = {
			0, 1, 2, 1, 3, 2, // front
			4, 6, 5, 5, 6, 7, // back
			2, 3, 6, 6, 3, 7, // up
			0, 4, 1, 1, 4, 5, // down
			0, 2, 4, 4, 2, 6, // left
			1, 5, 3, 5, 7, 3  // right
		};
		m_stride = 7;
		m_useTexture = false;
		m_shader = Globals::GetShader("default");

		BaseObject::Initialize();
	}

	void Cube::Update(float deltaTime)
	{
		BaseObject::Update(deltaTime);
	}

	void Cube::Render()
	{
		BaseObject::Render();
	}

}
