#include "TaskSystem.h"


namespace task {

	TaskSystem::TaskSystem(unsigned int threadsCount):
		m_stop{ false }
	{
		LOG("TaskSystem::constructor - Threads count is %d", threadsCount);
		for (size_t i = 0; i < threadsCount; i++) {
			m_threads.emplace_back([this]() { ThreadFunc(); });
		}
	}

	TaskSystem::~TaskSystem()
	{
		m_stop = true;
		m_taskCV.notify_all();
		for (auto& thread : m_threads) {
			if (thread.joinable()) {
				thread.join();
			}
		}
		m_threads.clear();
	}

	void TaskSystem::Update()
	{
		std::vector<std::string> completed;
		{
			std::lock_guard<std::mutex> lock(m_taskMutex);
			for (const auto& [path, _] : m_callbacks) {
				auto it = m_results.find(path);
				if (it != m_results.end()) {
					completed.push_back(path);
				}
			}
		}

		for (const auto& path : completed) {
			std::any result;
			std::function<void(const std::any&)> callback;
			{
				std::lock_guard<std::mutex> lock(m_taskMutex);
				result = m_results.at(path);
				callback = m_callbacks.at(path);
				m_results.erase(path);
				m_callbacks.erase(path);
			}
			if (result.has_value()) {
				callback(result);
			}
		}
	}

	void TaskSystem::ThreadFunc()
	{
		LOG("Created and looping thread %d", std::this_thread::get_id());
		while (true) {
			std::function<void()> task;
			{
				std::unique_lock<std::mutex> lock(m_taskMutex);
				m_taskCV.wait(lock, [this]() { return !m_tasks.empty() || m_stop.load(); });
				if (m_stop.load() && m_tasks.empty()) {
					return;
				}
				task = std::move(m_tasks.front());
				m_tasks.pop();
			}
			if (task) {
				task();
			}
		}
	}

}
