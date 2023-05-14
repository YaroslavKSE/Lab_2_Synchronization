#pragma once
#include <queue>
#include <thread>
#include <shared_mutex>

using read_write_lock = std::shared_mutex;
using read_lock = std::shared_lock<read_write_lock>;
using write_lock = std::unique_lock<read_write_lock>;
template <typename task_type_t>

class TaskQueue
{
private:
	using task_queue_implementation = std::queue<task_type_t>;
public:
	inline TaskQueue() = default;
	inline ~TaskQueue() { clear(); }
	inline bool empty() const;
	inline size_t size() const;
public:
	inline void clear();
	inline bool pop(task_type_t& task); 
	template <typename... arguments>
	inline void emplace(arguments&&... parameters);
public:
	TaskQueue(TaskQueue& other) = delete;
	TaskQueue(TaskQueue&& other) = delete;
	TaskQueue& operator=(TaskQueue& rhs) = delete;
	TaskQueue& operator=(TaskQueue&& rhs) = delete;
private:
	mutable read_write_lock m_rw_lock;
	task_queue_implementation m_tasks;
};
