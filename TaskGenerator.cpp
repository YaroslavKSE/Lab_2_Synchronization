#include "TaskGenerator.h"

int TaskGenerator::idCounter = 0;

TaskGenerator::TaskGenerator()
{
    
}

TaskGenerator::~TaskGenerator()
{

}

float generateRandomFloat(float min_value, float max_value) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(min_value, max_value);
	return dis(gen);
}

Task TaskGenerator::GenerateTask()
{
    Task newTask;
    float randomTime = generateRandomFloat(2.0, 15.0);
    newTask.taskTime = randomTime;
    newTask.id = idCounter++;
    return newTask;
}
