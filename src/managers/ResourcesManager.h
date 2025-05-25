#pragma once

#include <filesystem>
#include <unordered_map>
#include <string>
#include <memory>

#include "datas/ImageData.h"


class ResourcesManager {
public:
	ResourcesManager();
	~ResourcesManager();

	std::string ReadTextFromFile(const std::string& filePath, bool dontSave = false);
	ImageData* LoadImage(const std::string& imagePath);

private:
	std::string ReadText(const std::filesystem::path& filePath);
	std::filesystem::path ResolvePath(const std::string& path);

private:
	std::filesystem::path m_assetsPath;
	std::unordered_map<std::string, std::string> m_textFiles;
	std::unordered_map<std::string, std::unique_ptr<ImageData>> m_images;

};
