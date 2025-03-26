#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
class jungtable
{
public:
	std::vector<std::vector<int>> body;
	int push(int element);
	int del(int x, int y);
	void print();
};

