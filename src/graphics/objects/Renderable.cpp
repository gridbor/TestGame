#include "Renderable.h"

#include <glm/gtc/type_ptr.hpp>

#include "datas/ImageData.h"


namespace graphics {

	Renderable::Renderable() :
		m_vao{ 0 },
		m_vbo{ 0 },
		m_ebo{ 0 },
		m_stride{ 0 },
		m_useTexture{ false },
		m_matrix{ glm::mat4(1.f) },
		m_inited{ false },
		m_texture{ 0 },
		m_verticesBufferUsage{ GL_STATIC_DRAW },
		m_indicesBufferUsage{ GL_STATIC_DRAW },
		m_elementsDrawMode{ GL_TRIANGLES }
	{
		LOG("Renderable::constructor");
	}

	Renderable::~Renderable()
	{
		if (m_inited) {
			if (m_useTexture) {
				glDeleteTextures(1, &m_texture);
			}
			m_vertices.clear();
			m_indices.clear();
			glDeleteBuffers(1, &m_ebo);
			glDeleteBuffers(1, &m_vbo);
			glDeleteVertexArrays(1, &m_vao);
			m_shader.reset();
		}
		LOG("Renderable::~destructor");
	}

	void Renderable::Initialize()
	{
		m_inited = true;

		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		CreateBuffers(GL_ARRAY_BUFFER, &m_vbo, m_vertices, 1, m_verticesBufferUsage);
		CreateBuffers(GL_ELEMENT_ARRAY_BUFFER, &m_ebo, m_indices, 1, m_indicesBufferUsage);

		if (m_useTexture) {
			glGenTextures(1, &m_texture);
			glBindTexture(GL_TEXTURE_2D, m_texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, glm::value_ptr(glm::u8vec4(255, 0, 0, 255)));

			Globals::AsyncGetImageData(m_texturePath, [this](ImageData* imgData) {
				if (imgData) {
					GLint imgFormat = 0;
					switch (imgData->channels) {
					case 1: imgFormat = GL_RED; break;
					case 2: imgFormat = GL_RG; break;
					case 3: imgFormat = GL_RGB; break;
					case 4: imgFormat = GL_RGBA; break;
					}
					glBindTexture(GL_TEXTURE_2D, m_texture);
					glTexImage2D(GL_TEXTURE_2D, 0, imgFormat, imgData->width, imgData->height, 0, imgFormat, GL_UNSIGNED_BYTE, imgData->data);
					glGenerateMipmap(GL_TEXTURE_2D);
				}
				LOG("--- Texture loaded and linked to OpenGL, currentTime: %f", Globals::GetTime());
			});
		}

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * m_stride, (void*)0);
		glEnableVertexAttribArray(0);


		if (m_useTexture) {
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * m_stride, (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);

			if (auto shader = m_shader.lock(); shader != nullptr) {
				shader->SetUniform1i("u_texture", 0);
			}
		}
		else {
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * m_stride, (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
		}
	}

	void Renderable::Render()
	{
		if (!m_inited) return;

		auto shader = m_shader.lock();
		if (!shader) return;

		shader->Use();
		shader->SetUniformMatrix("u_model", m_matrix);

		if (m_useTexture) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_texture);
		}

		glBindVertexArray(m_vao);
		glDrawElements(m_elementsDrawMode, m_indices.size(), GL_UNSIGNED_INT, 0);
	}

	std::vector<glm::vec3> Renderable::GetVertices() const
	{
		std::vector<glm::vec3> vertices;
		for (size_t i = 0; i < m_vertices.size(); i += m_stride) {
			vertices.push_back(glm::vec3(m_vertices[i], m_vertices[i + 1], m_vertices[i + 2]));
		}
		return vertices;
	}

}
