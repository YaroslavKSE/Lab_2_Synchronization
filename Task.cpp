#include "Task.h"

int Task::idCounter = 0;

Task::Task()
{
	srand((unsigned) time(NULL));
	int randomTime = 2 + (rand() % 15);

	this->taskTime = randomTime;
	this->id = idCounter++;
}

Task::~Task()
{
	
}
