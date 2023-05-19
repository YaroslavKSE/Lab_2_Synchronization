#include <iostream>
#include "ThreadPool.h"
#include "TaskQueue.h"
#include "Task.h"
#include "TaskGenerator.h";
using namespace std;

// task #6


int main() {
	
	TaskQueue firstQueue;
	TaskQueue secondQueue;

	TaskGenerator taskGenerator;
	Task t1 = taskGenerator.GenerateTask();
	Task t2 =  taskGenerator.GenerateTask();
	Task t3 = taskGenerator.GenerateTask();;

	firstQueue.emplace(t1);
	firstQueue.emplace(t2);
	firstQueue.emplace(t3);
	float a = firstQueue.GetTotalTime();

	cout << a << endl;
	ThreadPool pool;
	pool.initialize(5);
	pool.add_task(t1);
	pool.add_task(t2);
	pool.add_task(t3);

	
	return 0;

}