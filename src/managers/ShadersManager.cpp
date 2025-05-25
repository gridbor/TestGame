#include "ShadersManager.h"

#include "tools/Logger.h"
#include "graphics/objects/Shader.h"


ShadersManager::ShadersManager()
{
	LOG("ShadersManager::constructor\n");
}

ShadersManager::~ShadersManager()
{
	m_shaders.clear();
	LOG("ShadersManager::~destructor\n");
}

void ShadersManager::Initialize()
{
	m_shaders["default"] = std::make_shared<graphics::Shader>("shaders/default.vs", "shaders/default.fs");
	m_shaders["default_textured"] = std::make_shared<graphics::Shader>("shaders/default_textured.vs", "shaders/default_textured.fs");
}

const std::shared_ptr<graphics::Shader> ShadersManager::GetShader(const std::string& shaderName) const
{
	auto shaderIt = m_shaders.find(shaderName);
	if (shaderIt != m_shaders.end()) {
		return shaderIt->second;
	}
	return nullptr;
}

std::vector<std::shared_ptr<graphics::Shader>> ShadersManager::GetAllShaders() const
{
	std::vector<std::shared_ptr<graphics::Shader>> result;
	for (auto it = m_shaders.begin(); it != m_shaders.end(); it++) {
		result.push_back(it->second);
	}
	return result;
}
