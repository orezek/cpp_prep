/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:15:57 by mbartos           #+#    #+#             */
/*   Updated: 2024/08/30 11:12:47 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>
#include <iostream>

#include "PmergeMe.hpp"

int main (int argc, char** argv)
{
	try
	{
		if (argc < 2)
			throw std::invalid_argument("Invalid input. Not enough arguments.");
		{
			PmergeMe<std::vector<unsigned int>, std::vector<std::pair<unsigned int, unsigned int> >  > pmergeVector;
			pmergeVector.Sort(argc, argv);
		}
		std::cout << std::endl;
		{
			PmergeMe<std::deque<unsigned int>, std::deque<std::pair<unsigned int, unsigned int> >  > pmergeDeque;
			pmergeDeque.Sort(argc, argv);
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (-1);
	}
	return (0);
}