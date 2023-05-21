#include "ThreadPool.h"

void ThreadPool::initialize(const size_t worker_count)
{
	write_lock _(m_rw_lock);
	if (m_initialized || m_terminated) {
		return;
	}
	m_workers.reserve(worker_count); 

	// Create worker threads for the first queue
	for (size_t id = 0; id < worker_count; id++) {
		m_workers.emplace_back(&ThreadPool::routine, this);
	}

	// Create worker threads for the second queue
	for (size_t id = worker_count / 2; id < worker_count; id++) {
		m_workers.emplace_back(&ThreadPool::routine, this);
	}

	m_initialized = !m_workers.empty();

}

void ThreadPool::terminate()
{
	{
		write_lock _(m_rw_lock);
		if (working_unsafe())
		{
			m_terminated = true;
		}
		else
		{
			m_workers.clear();
			m_terminated = false;
			m_initialized = false;
			return;
		}
	}
	m_task_waiter.notify_all();
	for (std::thread& worker : m_workers)
	{
		worker.join();
	}
	m_workers.clear();
	m_terminated = false;
	m_initialized = false;
}

void ThreadPool::routine()
{
	while (true)
	{
		bool task_acquired = false;
		Task task;
		{
			write_lock _(m_rw_lock);
			auto wait_condition = [this, &task_acquired, &task] {
				task_acquired = firstQueue.pop(task);	
				if (!task_acquired) {
					task_acquired = secondQueue.pop(task);
				}
				return m_terminated || task_acquired;
			};
			m_task_waiter.wait(_, wait_condition);
		}
		if (m_terminated && !task_acquired) {
			return;
		}
		
		std::cout << "Thread ID: " << std::this_thread::get_id() << "\n";
		std::cout << "Performing the task [id=" << task.id << " time=" << task.taskTime << "]" << "\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long>(task.taskTime * 1000)));
		std::cout << "The task is done, waiting for next" << "\n";
		m_task_waiter.notify_one();
	}

}

bool ThreadPool::working() const
{
	read_lock _(m_rw_lock);
	return working_unsafe();
}

bool ThreadPool::working_unsafe() const
{
	return m_initialized && !m_terminated;
}

void ThreadPool::add_task(Task& task)
{
	{
		read_lock _(m_rw_lock);
		if (!working_unsafe()) {
			return;
		}
	}

	//if (firstQueue.GetTotalTime() <= secondQueue.GetTotalTime()) {
	//	firstQueue.emplace(task);
	//}
	//else {
	//	secondQueue.emplace(task);
	//}


	// Determine the queue with the shortest total execution time
	TaskQueue& leastLoadedQueue = (firstQueue.GetTotalTime() < secondQueue.GetTotalTime()) ? firstQueue : secondQueue;

	leastLoadedQueue.emplace(task);
	m_task_waiter.notify_one();

}
