#pragma once

#include <string>
#include <glad/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace graphics {

	enum class ELocationType : unsigned char {
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
		void SetUniformMatrix(const std::string& name, const glm::mat4& matrix);
		void SetUniform1i(const std::string& name, int value);

	private:
		void StartCompile();
		GLuint CreateShader(GLenum type, const std::string& source);
		bool CheckStatus(GLenum type, GLuint id);

	private:
		GLuint m_programId;
		std::string m_vertexPath;
		std::string m_fragmentPath;

		struct ShaderSources {
			std::string vertex;
			std::string fragment;
			bool IsReady() const {
				return !vertex.empty() && !fragment.empty();
			}
			void Clear() {
				vertex.clear();
				fragment.clear();
			}
		} m_shaderSources;

		struct DeferredValues {
			std::unordered_map<std::string, glm::mat4> matrices;
			std::unordered_map<std::string, int> integers;
		} m_deferredValues;

	};

}
