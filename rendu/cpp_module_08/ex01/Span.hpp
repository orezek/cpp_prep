#pragma once

#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>
#include <algorithm>
#include <climits>

class Span
{
public:
	Span();
	explicit Span(unsigned int maxNums);
	Span(const Span&);
	Span& operator=(const Span&);
	~Span();

	void        addNumber(int newNumber);
	void        addMultipleN(int count);
	long int    longestSpan();
	long int    shortestSpan();
	void        printNumbers() const;

	/*------------------- exceptions -------------------*/
	class NotEnoughNumbersException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class MaxNumbersException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

private:
	static void             printInt(int element);
	unsigned int            _maxN;
	std::multiset<int>      _numbers;
};
