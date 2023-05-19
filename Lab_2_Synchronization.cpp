#include <iostream>
#include "ThreadPool.h"
#include "TaskQueue.h"
#include "Task.h"
using namespace std;

// task #6


int main() {
	
	TaskQueue firstQueue;
	TaskQueue secondQueue;

	Task t1;
	Task t2;
	Task t3;
	//firstQueue.emplace(t1);
	//firstQueue.emplace(t2);
	//secondQueue.emplace(t3);

	//firstQueue.clear();
	//secondQueue.size();

	ThreadPool pool;
	pool.initialize(5);
	pool.add_task(t1);
	pool.add_task(t2);
	pool.add_task(t3);
	return 0;

}