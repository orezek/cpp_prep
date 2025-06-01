/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:21:37 by mbartos           #+#    #+#             */
/*   Updated: 2024/07/25 12:17:15 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

template <typename T>
void addTwenty(T& num)
{
	num = num + 20;
}

void makeUpper(char& c)
{
	if(islower(c))
		c = toupper(c);
}

int main()
{
	std::cout << "------------- Add 20 to ints in array -------------" << std::endl;
	{
		int arr[3] = {1, 2, 3};

		std::cout << "Before iter:" << std::endl;
		for (std::size_t i = 0; i < 3; i++)
			std::cout << "arr[" << i << "] = " << arr[i] << std::endl;

 		iter(arr, 3, addTwenty<int>);

		std::cout << std::endl;

		std::cout << "After iter:" << std::endl;
		for (std::size_t i = 0; i < 3; i++)
			std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
	}
	std::cout << "------------ Add 20 to doubles in array ------------" << std::endl;
	{
		double arr[3] = {1.123, 2.456, 3.789};

		std::cout << "Before iter:" << std::endl;
		for (std::size_t i = 0; i < 3; i++)
			std::cout << "arr[" << i << "] = " << arr[i] << std::endl;

 		iter(arr, 3, addTwenty<double>);

		std::cout << std::endl;

		std::cout << "After iter:" << std::endl;
		for (std::size_t i = 0; i < 3; i++)
			std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
	}
	std::cout << "-------------- All chars to uppercase --------------" << std::endl;
	{
		char arr[15] = "Hi, evaluator!";

		std::cout << "Before iter:" << std::endl;
		std::cout << arr << std::endl;

 		iter(arr, 15, makeUpper);

		std::cout << std::endl;

		std::cout << "After iter:" << std::endl;
		std::cout << arr << std::endl;
	}
	std::cout << "----------------------------------------------------" << std::endl;
	return (0);
}