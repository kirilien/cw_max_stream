#pragma once
#include <string>
#include <iostream>
using namespace std;

class edge
{
public:
	string start;
	string finish;
	int capacity;

	edge()
	{
		start = '\0';
		finish = '\0';
		capacity = 0;
	}
	
	~edge() {}
};