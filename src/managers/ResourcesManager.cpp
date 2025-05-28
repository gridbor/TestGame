#include "ResourcesManager.h"

#include <fstream>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif
#undef STB_IMAGE_IMPLEMENTATION

#include "tools/Logger.h"
#include "tools/GameStorage.h"
#include "systems/TaskSystem.h"


ResourcesManager::ResourcesManager()
{
	LOG("ResourcesManager::constructor");
	m_assetsPath = std::filesystem::current_path();
	while (!std::filesystem::exists(m_assetsPath / "assets")) {
		if (!m_assetsPath.has_parent_path()) {
			throw std::runtime_error("Assets directory not found!\n");
		}
		m_assetsPath = m_assetsPath.parent_path();
	}
	m_assetsPath /= "assets";
	LOG("Assets path: %s", m_assetsPath.string().c_str());
}

ResourcesManager::~ResourcesManager()
{
	m_textFiles.clear();
	m_images.clear();
	m_assetsPath.clear();
	LOG("ResourcesManager::~destructor");
}

std::string ResourcesManager::ReadTextFile(const std::string& filePath, bool dontSave)
{
	auto it = m_textFiles.find(filePath);
	if (it != m_textFiles.end()) {
		LOG("Text File \"%s\" found in loaded texts", filePath.c_str());
		return it->second;
	}
	std::string text = ReadText(ResolvePath(filePath));
	if (!dontSave && !text.empty()) {
		m_textFiles[filePath] = text;
	}
	return text;
}

ImageData* ResourcesManager::LoadImage(const std::string& imagePath)
{
	auto imageIt = m_images.find(imagePath);
	if (imageIt != m_images.end()) {
		return imageIt->second.get();
	}

	ImageData* imageData = new ImageData();
	stbi_set_flip_vertically_on_load(true);
	imageData->data = stbi_load(ResolvePath(imagePath).string().c_str(), &imageData->width, &imageData->height, &imageData->channels, 4);
	m_images[imagePath].reset(imageData);
	return m_images[imagePath].get();
}

void ResourcesManager::AsyncReadTextFile(const std::string& filePath, std::function<void(const std::string&)> callback)
{
	auto it = m_textFiles.find(filePath);
	if (it != m_textFiles.end()) {
		LOG("Text File \"%s\" found in loaded texts", filePath.c_str());
		callback(it->second);
		return;
	}

	std::function<const std::string&()> loader = [=]()->const std::string& {
		m_textFiles[filePath] = ReadText(ResolvePath(filePath));
		return m_textFiles[filePath];
	};

	Globals::GetSystem<task::TaskSystem>(ESystemType::TASK)->CreateLoadTask(filePath, loader, callback);
}

void ResourcesManager::AsyncLoadImage(const std::string& imagePath, std::function<void(ImageData*)> callback)
{
	auto imageIt = m_images.find(imagePath);
	if (imageIt != m_images.end()) {
		if (callback) callback(imageIt->second.get());
		return;
	}

	std::function<ImageData*()> loader = [=]()->ImageData* {
		ImageData* imageData = new ImageData();
		stbi_set_flip_vertically_on_load(true);
		imageData->data = stbi_load(ResolvePath(imagePath).string().c_str(), &imageData->width, &imageData->height, &imageData->channels, 4);
		m_images[imagePath].reset(imageData);
		return imageData;
	};

	Globals::GetSystem<task::TaskSystem>(ESystemType::TASK)->CreateLoadTask(imagePath, loader, callback);
}

std::string ResourcesManager::ReadText(const std::filesystem::path& filePath)
{
	std::string text;
	std::fstream file;
	file.open(filePath.string().c_str(), std::ios::in);
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			text += line + '\n';
		}
	}
	else {
		LOG("Text File \"%s\" open failed!", filePath.string().c_str());
	}
	file.close();
	return text;
}

std::filesystem::path ResourcesManager::ResolvePath(const std::string& path)
{
	std::filesystem::path filePath(path);
	if (std::filesystem::exists(filePath)) {
		return filePath;
	}
	else if (std::filesystem::exists(m_assetsPath / filePath)) {
		return m_assetsPath / filePath;
	}
	LOG("- Path \"%s\" not found!", path.c_str());
	return std::filesystem::path();
}
