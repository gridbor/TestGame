#include "Logger.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <string>


Logger::Logger()
{
	printf("Logger::constructor\n");
	m_logPath = std::filesystem::current_path() / "Log.log";

	if (std::filesystem::exists(m_logPath)) {
		ClearOldLogFiles();
		// rename previous log file
		std::filesystem::file_time_type last_time = std::filesystem::last_write_time(m_logPath);
		const auto sys_time = std::chrono::clock_cast<std::chrono::system_clock>(last_time);
		const auto time = std::chrono::system_clock::to_time_t(sys_time);
		const auto lt = localtime(&time);
		std::string log_with_date_str = std::format("Log__{:#02}{:#02}{}_{:#02}{:#02}{:#02}.log", lt->tm_mday, lt->tm_mon + 1, 1900 + lt->tm_year, lt->tm_hour, lt->tm_min, lt->tm_sec);
		std::filesystem::rename(m_logPath, std::filesystem::current_path() / log_with_date_str);
	}
	m_logFileStream.open(m_logPath, std::ios::out | std::ios::app);
}

Logger::~Logger()
{
	m_logFileStream.close();
	printf("Logger::~destructor\n");
}

void Logger::Log(const char* const fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	char buffer[1025];

	if (args == NULL) {
		strcpy_s(buffer, fmt);
	}
	else {
		vsprintf_s(buffer, fmt, args);
	}
	va_end(args);

	std::string bufferStr = buffer;
	if (!bufferStr.ends_with("\n")) {
		bufferStr += "\n";
	}
	OutputDebugString(bufferStr.c_str());
	printf(bufferStr.c_str());
	if (m_logFileStream.is_open()) {
		const auto current = std::chrono::system_clock::now();
		const auto sys_time = std::chrono::system_clock::to_time_t(current);
		const auto lt = localtime(&sys_time);
		const auto ms = std::chrono::duration_cast<std::chrono::microseconds>(current.time_since_epoch());
		m_logFileStream << std::format("{:#02}:{:#02}:{:#02}.{:06}: ", lt->tm_hour, lt->tm_min, lt->tm_sec, ms.count() % 1000000);
		m_logFileStream << bufferStr;
	}
}

void Logger::ClearOldLogFiles()
{
	std::vector<std::pair<std::filesystem::path, time_t>> prev_log_files;
	time_t newest = 0;
	for (const auto& log_file : std::filesystem::directory_iterator(m_logPath.parent_path())) {
		std::filesystem::path log_path = log_file.path();
		if (log_path.extension() == ".log") {
			std::filesystem::path fname = log_path.filename();
			std::string fname_str = fname.string();
			if (fname_str.find("__") != std::string::npos) {
				tm t{ 0 };
				t.tm_mday = std::stoi(fname_str.substr(5, 2));
				t.tm_mon = std::stoi(fname_str.substr(7, 2)) - 1;
				t.tm_year = std::stoi(fname_str.substr(9, 4)) - 1900;
				t.tm_hour = std::stoi(fname_str.substr(14, 2));
				t.tm_min = std::stoi(fname_str.substr(16, 2));
				t.tm_sec = std::stoi(fname_str.substr(18, 2));
				time_t tvalue = std::mktime(&t);
				prev_log_files.emplace_back(log_path, tvalue);
				if (newest == 0 || newest < tvalue) {
					newest = tvalue;
				}
			}
		}
	}
	if (!prev_log_files.empty()) {
		for (const auto& prev_pair : prev_log_files) {
			if (prev_pair.second != newest) {
				std::filesystem::remove(prev_pair.first);
			}
		}
		prev_log_files.clear();
	}
}
