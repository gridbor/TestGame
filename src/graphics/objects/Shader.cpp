#include "Shader.h"

#include <functional>

#include "tools/Logger.h"
#include "GameApp.h"
#include "tools/GameStorage.h"
#include "managers/ResourcesManager.h"


namespace graphics {

	Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		LOG("Shader::constructor");

		GLuint vertexShaderId = CreateShader(GL_VERTEX_SHADER, Globals::ReadTextFile(vertexShaderPath, true));
		GLuint fragmentShaderId = CreateShader(GL_FRAGMENT_SHADER, Globals::ReadTextFile(fragmentShaderPath, true));
		if (vertexShaderId == 0 || fragmentShaderId == 0) {
			m_programId = 0;
			return;
		}

		m_programId = glCreateProgram();
		glAttachShader(m_programId, vertexShaderId);
		glAttachShader(m_programId, fragmentShaderId);
		glLinkProgram(m_programId);

		bool linkFailed = !CheckStatus(GL_LINK_STATUS, m_programId);
		std::function<void(GLuint)> RemoveShader = [this](GLuint sId) {
			glDetachShader(m_programId, sId);
			glDeleteShader(sId);
		};

		RemoveShader(vertexShaderId);
		RemoveShader(fragmentShaderId);

		if (linkFailed) {
			glDeleteProgram(m_programId);
			m_programId = 0;
		}

		LOG("Shader Program ID: %u", m_programId);
	}

	Shader::~Shader()
	{
		glUseProgram(0);
		if (m_programId != 0) {
			glDeleteProgram(m_programId);
		}
		LOG("Shader::~destructor");
	}

	void Shader::Use() const
	{
		glUseProgram(m_programId);
	}

	GLint Shader::GetLocation(const ELocationType& type, const std::string& name)
	{
		switch (type) {
		case ELocationType::ATTRIBUTE: return glGetAttribLocation(m_programId, name.c_str()); break;
		case ELocationType::UNIFORM: return glGetUniformLocation(m_programId, name.c_str()); break;
		}
		return -1;
	}

	void Shader::SetUniform(const std::string& name, const glm::mat4& matrix)
	{
		glProgramUniformMatrix4fv(m_programId, GetLocation(ELocationType::UNIFORM, name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	GLuint Shader::CreateShader(GLenum type, const std::string& source)
	{
		GLuint shaderId = glCreateShader(type);
		const char* shaderStr = source.c_str();
		glShaderSource(shaderId, 1, &shaderStr, nullptr);
		glCompileShader(shaderId);

		if (!CheckStatus(GL_COMPILE_STATUS, shaderId)) {
			glDeleteShader(shaderId);
			shaderId = 0;
		}

		return shaderId;
	}

	bool Shader::CheckStatus(GLenum type, GLuint id)
	{
		GLint result;
		std::function<void(GLuint, GLsizei, GLsizei*, GLchar*)> infoCallback = nullptr;
		std::string formatStr;
		switch (type)
		{
		case GL_COMPILE_STATUS:
			glGetShaderiv(id, type, &result);
			infoCallback = glGetShaderInfoLog;
			formatStr = "Shader::CheckStatus - Shader \"%u\" compiling error:\n    %s";
			break;
		case GL_LINK_STATUS:
			glGetProgramiv(id, type, &result);
			infoCallback = glGetProgramInfoLog;
			formatStr = "Shader::CheckStatus - Program \"%u\" linking error:\n    %s";
			break;
		default:
			LOG("Shader::CheckStatus - UNKNOWN type %u", type);
			return false;
		}
		if (result != GL_TRUE) {
			int length = 0;
			char info[1025];
			infoCallback(id, 1025, &length, info);
			LOG(formatStr.c_str(), id, info);
			return false;
		}
		return true;
	}

}
