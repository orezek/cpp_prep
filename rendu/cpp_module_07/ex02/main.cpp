/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:21:37 by mbartos           #+#    #+#             */
/*   Updated: 2024/07/25 13:54:35 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

int	main()
{
	std::cout << "----------------------------------------------------" << std::endl;
	{
		Array<unsigned int> array(5);

		// Fill the array
		for (unsigned int i = 0; i < 5; i++)
			array[i] = 20 + i;

		// Print the array
		for (unsigned int i = 0; i < 5; i++)
			std::cout << "array[" << i << "] = " << array[i] << std::endl;

		// Coppy array to coppiedArray
		Array<unsigned int> coppiedArray(array);

		// Print coppeidArray
		for (unsigned int i = 0; i < 5; i++)
			std::cout << "coppiedArray[" << i << "] = " << coppiedArray[i] << std::endl;
	}
	std::cout << "----------------------------------------------------" << std::endl;
	{
		Array<unsigned int> array1(5);

		// Fill the array
		for (unsigned int i = 0; i < 5; i++)
			array1[i] = 20 + i;

		// Print the array
		for (unsigned int i = 0; i < 5; i++)
			std::cout << "array[" << i << "] = " << array1[i] << std::endl;

		Array<unsigned int> array2(3);

		// Fill the array
		for (unsigned int i = 0; i < 3; i++)
			array2[i] = 100 + i;

		std::cout << std::endl << "--------------------------" << std::endl;
		// Print the array
		for (unsigned int i = 0; i < 3; i++)
			std::cout << "array2[" << i << "] = " << array2[i] << std::endl;

		array1 = array2;

		std::cout << std::endl << "----- array = array2 -----" << std::endl;
		// Print the array
		for (unsigned int i = 0; i < 3; i++)
			std::cout << "array[" << i << "] = " << array1[i] << std::endl;
		std::cout << std::endl;
	}
	std::cout << "----------------------------------------------------" << std::endl;
	{
		Array<int> array(5);
		// Try to reach the index outside of the range
		try
		{
			array[21] = 1;
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << '\n';
		}

		// Try to reach the index outside of the range
		try
		{
			array[-1] = 1;
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << '\n';
		}
	}
	std::cout << "----------------------------------------------------" << std::endl;
}