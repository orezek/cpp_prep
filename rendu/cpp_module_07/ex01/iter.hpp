#pragma once
#include <iostream>

template<typename T> void iter(T* array, unsigned int size, void (*func)(T&))
{
	for (std::size_t i = 0; i < size; i++)
		func(array[i]);
}
