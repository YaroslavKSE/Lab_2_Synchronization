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
	 void add_task(Task& task);
public:
	ThreadPool(ThreadPool& other) = delete;
	ThreadPool(ThreadPool&& other) = delete;
	ThreadPool& operator=(ThreadPool& rhs) = delete;
	ThreadPool& operator=(ThreadPool&& rhs) = delete;
private:
	mutable read_write_lock m_rw_lock;
	mutable std::condition_variable_any m_task_waiter;

	std::vector<std::thread> m_workers;
	TaskQueue firstQueue;
	TaskQueue secondQueue;
	bool m_initialized = false;
	bool m_terminated = false;
};
