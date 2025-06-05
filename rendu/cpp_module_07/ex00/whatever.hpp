#pragma once
#include <iostream>

template <typename T> void swap(T& arg1, T& arg2)
{
	T tmpArg;

	tmpArg = arg1;
	arg1 = arg2;
	arg2 = tmpArg;
};

template <typename T> const T& min(const T& arg1, const T& arg2)
{
	return (arg1 <= arg2 ? arg1 : arg2);
};

template <typename T> const T& max(const T& arg1, const T& arg2)
{
	return (arg1 >= arg2 ? arg1 : arg2);
};
