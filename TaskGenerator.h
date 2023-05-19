#pragma once
#include "Task.h"
#include<iostream>
#include<cstdlib>
#include <random>

using namespace std;

class TaskGenerator
{
public:
	TaskGenerator();
	~TaskGenerator();
	Task GenerateTask();
private:
	static int idCounter;
};

