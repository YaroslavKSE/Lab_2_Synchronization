#pragma once
#include<iostream>
#include<cstdlib>
using namespace std;
class Task
{
public:
	Task();
	~Task();
	int taskTime;
private:
	int id;
	static int idCounter;

};

