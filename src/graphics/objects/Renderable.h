#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "tools/Logger.h"
#include "Shader.h"


namespace graphics {

	class Renderable {
	protected:
		Renderable();

	public:
		virtual ~Renderable();

		virtual void Initialize();
		virtual void Render();

		std::vector<glm::vec3> GetVertices() const;

	protected:
		template<class T>
		void CreateBuffers(GLenum type, GLuint* buffersId, const std::vector<T>& vec, GLuint buffersCount = 1, GLenum usage = GL_STATIC_DRAW) {
			glGenBuffers(buffersCount, buffersId);
			glBindBuffer(type, *buffersId);
			glBufferData(type, vec.size() * sizeof(T), vec.data(), usage);
		}

	protected:
		bool m_inited;
		bool m_useTexture;
		GLuint m_vao;
		GLuint m_vbo;
		GLuint m_ebo;
		GLuint m_texture;
		unsigned int m_stride;
		std::vector<float> m_vertices;
		std::vector<unsigned int> m_indices;
		GLenum m_verticesBufferUsage;
		GLenum m_indicesBufferUsage;
		GLenum m_elementsDrawMode;
		std::weak_ptr<Shader> m_shader;
		std::string m_texturePath;
		glm::mat4 m_matrix;

	};

}
