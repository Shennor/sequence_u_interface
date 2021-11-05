#pragma once
#include <iostream>

inline int get_value()
{
	std::cout << "Enter number >> ";
	int value;
	std::cin >> value;
	return value;
}
