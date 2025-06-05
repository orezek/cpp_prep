#pragma once

#include <iostream>
#include <exception>
#include <algorithm>

class ValueNotFound : public std::exception
{
	public:
		virtual const char *what() const throw();
};

const char* ValueNotFound::what() const throw() {
    return "Value not found in the container.";
}

template <typename T>
void	easyfind(const T& container, int num)
{
	typename T::const_iterator it;

	it = std::find(container.begin(), container.end(), num);

	if (it != container.end())
		std::cout << "Element '" << *it << "' was found." << std::endl;
	else
		throw ValueNotFound();
	return ;
}
