#include "Quad.h"

#include "Globals.h"
#include "GameApp.h"
#include "tools/GameStorage.h"
#include "managers/ShadersManager.h"
#include "graphics/objects/helpers/Coord.h"


namespace mesh {

	Quad::Quad()
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
	}

	void Quad::Render()
	{
		BaseObject::Render();
	}

}
