#pragma once

#include <filesystem>
#include <functional>
#include <unordered_map>
#include <string>
#include <memory>
#include <future>

#include "datas/ImageData.h"


class ResourcesManager {
public:
	ResourcesManager();
	~ResourcesManager();

	std::string ReadTextFile(const std::string& filePath, bool dontSave = false);
	ImageData* LoadImage(const std::string& imagePath);

	// async
	void AsyncReadTextFile(const std::string& filePath, std::function<void(const std::string&)> callback, bool dontSave = false);
	void AsyncLoadImage(const std::string& imagePath, std::function<void(ImageData*)> callback);

private:
	std::string ReadText(const std::filesystem::path& filePath);
	std::filesystem::path ResolvePath(const std::string& path);

private:
	std::filesystem::path m_assetsPath;
	std::unordered_map<std::string, std::string> m_textFiles;
	std::unordered_map<std::string, std::unique_ptr<ImageData>> m_images;

};
