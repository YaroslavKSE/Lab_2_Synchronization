#include "TaskQueue.h"


TaskQueue::~TaskQueue()
{
}

bool TaskQueue::empty() const
{
	read_lock _(m_rw_lock);
	return m_tasks.empty();
}


size_t TaskQueue::size() const
{
	read_lock _(m_rw_lock);
	return m_tasks.size();
}


void TaskQueue::clear()
{
	write_lock _(m_rw_lock);
	while (!m_tasks.empty())
	{
		m_tasks.pop();
	}
}

bool TaskQueue::pop(Task& task)
{
	write_lock _(m_rw_lock);
	if (m_tasks.empty())
	{
		return false;
	}
	else
	{
		task = std::move(m_tasks.front());
		m_tasks.pop();
		return true;
	}
}

void TaskQueue::emplace(Task& task)
{
	write_lock _(m_rw_lock);
	m_tasks.emplace(task);
}

float TaskQueue::GetTotalTime() {
	read_lock _(m_rw_lock);
	float totalTime = 0;
	for (int i = 0; i < m_tasks.size(); i++) {
		totalTime += m_tasks.front().taskTime;
	}
	return totalTime;
}
