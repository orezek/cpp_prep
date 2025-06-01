/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:24:17 by mbartos           #+#    #+#             */
/*   Updated: 2024/07/31 14:37:32 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span() : maxNumbers(0) {};

Span::Span(unsigned int maxNums) : maxNumbers(maxNums) {};

Span::Span(const Span& refObj) : maxNumbers(refObj.maxNumbers) {};

Span& Span::operator=(const Span& refObj)
{
	maxNumbers = refObj.maxNumbers;
	return (*this);
};

Span::~Span() {};

void Span::addNumber(int newNumber)
{
	if (numbers.size() < maxNumbers && maxNumbers != 0)
		numbers.insert(newNumber);
	else
		throw MaxNumbers();
};

void Span::addManyNumbers(int count)
{
	if (numbers.size() == maxNumbers)
		throw MaxNumbers();
	if (count + numbers.size() > maxNumbers)
	{
		count = maxNumbers - numbers.size();
		std::cout << "Max limit of numbers would be reached. Only " << count << " random numbers will be added to span." << std::endl;
	}

	srand(time(0));
	std::vector<int> range;
	int number;
	for (int i = 0; i != count; ++i)
	{
		number = rand();
		range.push_back(number);
	}
	numbers.insert(range.begin(), range.end());
	// std::cout << "Span size is: " << numbers.size() << " and max size is: " << maxNumbers << std::endl;
}

long int Span::longestSpan()
{
	if (numbers.size() < 2)
		throw NotEnoughNumbers();

	long int result = labs(static_cast<long int>(*numbers.rbegin()) - static_cast<long int>(*numbers.begin()));
	return (result);
};

long int Span::shortestSpan()
{
	if (numbers.size() < 2)
		throw NotEnoughNumbers();

	long int difference = INT_MAX;
	std::multiset<int>::const_iterator it = numbers.begin();
	long int temp_number = static_cast<long int>(*it);

	for (++it; it != numbers.end(); ++it)
	{
		if (labs(temp_number - static_cast<long int>(*it)) < difference)
			difference = labs(temp_number - static_cast<long int>(*it));
		temp_number = static_cast<long int>(*it);
	}	
	return (difference);
};

void Span::printInt(int number)
{
	std::cout << number << ", ";
};

void Span::printNumbers() const
{
	std::cout << "Numbers: ";
	std::for_each(numbers.begin(), numbers.end(), Span::printInt);
	std::cout << std::endl;
};

const char* Span::NotEnoughNumbers::what() const throw()
{
	return "There is not enough numbers in Span!";
};

const char* Span::MaxNumbers::what() const throw()
{
	return "Max limit of numbers in Span reached!";
};