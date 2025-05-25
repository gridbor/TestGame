#pragma once

#include <string>
#include <glad/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace graphics {

	enum class ELocationType : char {
		NONE = 0,
		ATTRIBUTE,
		UNIFORM
	};

	class Shader {
	public:
		Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		~Shader();

		GLuint GetProgramId() const { return m_programId; }

		void Use() const;
		GLint GetLocation(const ELocationType& type, const std::string& name);
		void SetUniform(const std::string& name, const glm::mat4& matrix);

	private:
		GLuint CreateShader(GLenum type, const std::string& source);
		bool CheckStatus(GLenum type, GLuint id);

	private:
		GLuint m_programId;

	};

}
