#pragma once
#include <iostream>
#include "vector"
#include "string"

class Debug
{
public:
	template<typename T>
	static void printArray(std::vector<T> array);
	template<typename T>
	static void printArray(T array[], int size);
};