#pragma once
#include <vector>
#include <deque>
#include <string>

template <typename T>
std::string getTypeName() {
	return "Unknown type";
}

// Specializations for known types
template <>
std::string getTypeName<std::vector<unsigned int> >() {
	return "std::vector";
}

template <>
std::string getTypeName<std::deque<unsigned int> >() {
	return "std::deque";
}
