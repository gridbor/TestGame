#pragma once

#include <cstdarg>
#include <string>
#include <filesystem>
#include <fstream>

#include "Globals.h"


#define LOG(x, ...) Globals::Get()->GetLogger()->Log(x, __VA_ARGS__);


class Logger {
public:
	Logger();
	~Logger();

	void Log(const char* const fmt, ...);

private:
	void ClearOldLogFiles();

private:
	std::filesystem::path m_logPath;
	std::ofstream m_logFileStream;

};
