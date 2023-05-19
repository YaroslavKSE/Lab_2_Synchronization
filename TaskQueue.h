#pragma once
#include <queue>
#include <thread>
#include <shared_mutex>
#include "Task.h"

using read_write_lock = std::shared_mutex;
using read_lock = std::shared_lock<read_write_lock>;
using write_lock = std::unique_lock<read_write_lock>;


class TaskQueue
{
private:
	using task_queue_implementation = std::queue<Task>;
public:
	TaskQueue() = default;
	~TaskQueue();
	bool empty() const;
	size_t size() const;
public:
	void clear();
	bool pop(Task& task); 
	void emplace(Task& task);
public:
	TaskQueue(TaskQueue& other) = delete;
	TaskQueue(TaskQueue&& other) = delete;
	TaskQueue& operator=(TaskQueue& rhs) = delete;
	TaskQueue& operator=(TaskQueue&& rhs) = delete;
private:
	mutable read_write_lock m_rw_lock;
	task_queue_implementation m_tasks;
};
