#include "TestRect.h"

#include "Globals.h"
#include "GameApp.h"
#include "Transform.h"
#include "tools/GameStorage.h"
#include "managers/ShadersManager.h"


namespace graphics {

	TestRect::TestRect()
	{
		LOG("TestRect::constructor");
	}

	TestRect::~TestRect()
	{
		LOG("TestRect::~destructor");
	}

	void TestRect::Initialize()
	{
		m_vertices = {
			-0.25f, -0.25f,  0.f,  0.f, 0.f,
			 0.25f, -0.25f,  0.f,  1.f, 0.f,
			 0.25f,  0.25f,  0.f,  1.f, 1.f,
			-0.25f,  0.25f,  0.f,  0.f, 1.f
		};
		m_indices = { 0, 1, 2, 0, 2, 3 };
		m_stride = 5;

		m_shader = Globals::GetShader("default_textured");

		m_useTexture = true;
		m_texturePath = "images/triangle.png";

		BaseObject::Initialize();
	}

	void TestRect::Render()
	{
		BaseObject::Render();
	}

}
