#pragma once

#include <thread>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <vector>
#include <functional>
#include <future>
#include <memory>
#include <unordered_map>
#include <string>
#include <any>

#include "tools/Logger.h"


namespace task {

	class TaskSystem {
	public:
		explicit TaskSystem(unsigned int threadsCount = std::thread::hardware_concurrency());
		~TaskSystem();

		void Update();

		template<typename T>
		void CreateLoadTask(const std::string& path, std::function<T()> loadFunc, std::function<void(T)> callback) {
			{
				std::lock_guard<std::mutex> lock(m_taskMutex);
				m_callbacks[path] = [callback](const std::any& result) {
					if (result.type() == typeid(T)) {
						callback(std::any_cast<T>(result));
					}
				};
			}
			PushQueueTask([=]() -> std::any {
				try {
					T result = loadFunc();
					{
						std::lock_guard<std::mutex> lock(m_taskMutex);
						m_results[path] = result;
					}
					return result;
				}
				catch (...) {
					LOG("Task %d working error!", std::this_thread::get_id());
					return std::any{};
				}
			});
		}

	private:
		template<typename T>
		auto PushQueueTask(T task) -> std::future<decltype(task())> {
			using ReturnType = decltype(task());
			auto* package = new std::packaged_task<ReturnType()>(std::move(task));
			std::future<ReturnType> result = package->get_future();
			{
				std::lock_guard<std::mutex> lock(m_taskMutex);
				m_tasks.push([package]() { (*package)(); delete package; });
			}
			m_taskCV.notify_one();
			return result;
		}

		void ThreadFunc();

	private:
		std::vector<std::thread> m_threads;
		std::queue<std::function<void()>> m_tasks;
		mutable std::mutex m_taskMutex;
		std::condition_variable m_taskCV;
		std::atomic<bool> m_stop;
		std::unordered_map<std::string, std::function<void(const std::any&)>> m_callbacks;
		std::unordered_map<std::string, std::any> m_results;

	};

}
