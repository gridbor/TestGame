#pragma once

#include <string>
#include <unordered_map>
#include <memory>


namespace graphics {
	class Shader;
}

class ShadersManager {
public:
	ShadersManager();
	~ShadersManager();

	void Initialize();

	const std::shared_ptr<graphics::Shader> GetShader(const std::string& shaderName) const;
	std::vector<std::shared_ptr<graphics::Shader>> GetAllShaders() const;

private:
	std::unordered_map<std::string, std::shared_ptr<graphics::Shader>> m_shaders;

};
