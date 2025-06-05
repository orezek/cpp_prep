#pragma once

#include <iostream>
#include <cstdlib>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <climits>

class Span 
{
	public:
		Span();
		Span(unsigned int maxNums);
		Span(const Span&);
		Span& operator=(const Span&);
		~Span();

		void		addNumber(int newNumber);
		void		addManyNumbers(int count);
		long int	longestSpan();
		long int	shortestSpan();
		void		printNumbers() const;

	class NotEnoughNumbers : public std::exception
	{
		public:
			virtual const char *what() const throw();
	};

	class MaxNumbers : public std::exception
	{
		public:
			virtual const char *what() const throw();
	};

	private:
		static void			printInt(int element);
		unsigned int		maxNumbers;
		std::multiset<int>	numbers;
};
