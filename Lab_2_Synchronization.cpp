#include <iostream>
#include "ThreadPool.h"
#include "TaskQueue.h"
#include "Task.h"
#include "TaskGenerator.h";
using namespace std;

// task #6


int main() {
	
    
    ThreadPool threadPool;

    const size_t workerCount = 4;  // Adjust the number of worker threads as needed
    threadPool.initialize(workerCount);

    TaskGenerator taskGenerator;

    const size_t numTasks = 20;  // Adjust the number of tasks as needed
    for (size_t i = 0; i < numTasks; i++) {
        Task task = taskGenerator.GenerateTask();
        threadPool.add_task(task);
    }

    threadPool.terminate();

    return 0;

}