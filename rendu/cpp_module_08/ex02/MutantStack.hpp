#pragma once
#include <stack>
#include <algorithm>
#include <iostream>

template <class T>
class MutantStack : public std::stack<T>
{
	// inherits from stack

	public:
		MutantStack(){}
		~MutantStack(){}
		MutantStack(const MutantStack &stack) { *this = stack; }
		// assignment operator is used from stack class

		// This line defines a type alias iterator for the iterator type of the underlying container used by std::stack<T>.
		// std::stack is typically implemented using another container (like std::deque or std::vector).
		// The container_type is a type alias in std::stack that represents this underlying container type.
		// By accessing container_type::iterator, you're referring to the iterator type of that container.
		typedef typename std::stack<T>::container_type::iterator iterator;
		typedef typename std::stack<T>::container_type::const_iterator const_iterator;

		// this->c refers to the underlying container in std::stack<T>.
		// The begin() function of the underlying container returns an iterator pointing to the first element.
		iterator begin()
		{
			return this->c.begin();
		}
		const_iterator begin() const
		{
			return this->c.begin();
		}

		iterator end()
		{
			return this->c.end();
		}
		const_iterator end() const
		{
			return this->c.end();
		}
};
