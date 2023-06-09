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

    //const size_t numTasks = 30;  // Adjust the number of tasks as needed
    //for (size_t i = 0; i < numTasks; i++) {

    //    Task task = taskGenerator.GenerateTask();
    //    std::this_thread::sleep_for(std::chrono::seconds(1));  // Delay before adding the task
    //    threadPool.add_task(task);
    //}

    while (true) {

    Task task = taskGenerator.GenerateTask();
    std::this_thread::sleep_for(std::chrono::seconds(1));  // delay before adding the task
    threadPool.add_task(task);
    }

    threadPool.terminate();

    return 0;

}