#include <iostream>
#include "TaskQueue.h"
#include "ThreadPool.h"
#include "Task.h"
using namespace std;

// task #6


int main() {
	TaskQueue firstQueue;
	TaskQueue secondQueue;

	Task t1;
	Task t2;
	Task t3;
	firstQueue.emplace(t1);
	firstQueue.emplace(t2);
	secondQueue.emplace(t3);

	firstQueue.clear();
	secondQueue.size();

	return 0;

}