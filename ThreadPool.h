#pragma once

#include "TaskQueue.h"
#include <vector>
#include <functional>

class ThreadPool
{
public:
inline ThreadPool() = default;
inline ~ThreadPool() { terminate(); }
public:
	void initialize(const size_t worker_count);
	void terminate();
	void routine();
	bool working() const;
	bool working_unsafe() const;
public:
	template <typename task_t, typename... arguments>
	inline void add_task(task_t&& task, arguments&&... parameters);
public:
	ThreadPool(ThreadPool& other) = delete;
	ThreadPool(ThreadPool&& other) = delete;
	ThreadPool& operator=(ThreadPool& rhs) = delete;
	ThreadPool& operator=(ThreadPool&& rhs) = delete;
private:
	mutable read_write_lock m_rw_lock;
	mutable std::condition_variable_any m_task_waiter;

	std::vector<std::thread> m_workers;
	TaskQueue<std::function<void()>> m_tasks;
	bool m_initialized = false;
	bool m_terminated = false;
};

template<typename task_t, typename ...arguments>
inline void ThreadPool::add_task(task_t&& task, arguments && ...parameters)
{
	{
		read_lock _(m_rw_lock);
		if (!working_unsafe())
		{
			return;
		}
	}
	auto bind = std::bind(std::forward<task_t>(task),
		std::forward<arguments>(parameters)...);
	m_tasks.emplace(bind);
	m_task_waiter.notify_one();
}
