#include "Array.hpp"

int	main()
{
	std::cout << "----- CASE 1: --------------------------------" << std::endl;
	{
		Array<unsigned int> array(5);

		// Fill the array
		for (unsigned int i = 0; i < 5; i++)
			array[i] = 20 + i;

		// Print the array
		for (unsigned int i = 0; i < 5; i++)
			std::cout << "array[" << i << "] = " << array[i] << std::endl;

		// Invoke copy constructor to create a new copy
		Array<unsigned int> coppiedArray(array);

		// Print the new copy
		for (unsigned int i = 0; i < 5; i++)
			std::cout << "coppiedArray[" << i << "] = " << coppiedArray[i] << std::endl;
	}
	std::cout << "------ CASE 2: ------ test assignment operaotr ------------------" << std::endl;
	{

        // Array 1
		Array<unsigned int> array1(5);

		// Fill the array
		for (unsigned int i = 0; i < 5; i++)
			array1[i] = 20 + i;

		// Print the array 1
		for (unsigned int i = 0; i < 5; i++)
			std::cout << "array[" << i << "] = " << array1[i] << std::endl;

        // Array 2
		Array<unsigned int> array2(3);

		// Fill the array
		for (unsigned int i = 0; i < 3; i++)
			array2[i] = 100 + i;

		std::cout << std::endl << "--------------------------" << std::endl;
		// Print the array 2
		for (unsigned int i = 0; i < 3; i++)
			std::cout << "array2[" << i << "] = " << array2[i] << std::endl;

        // Invoke assignment operator and make one to contain elements from 2
		array1 = array2;

		std::cout << std::endl << "----- array = array2 -----" << std::endl;
		// Print the array 1 with the conent of array 2
		for (unsigned int i = 0; i < 3; i++)
			std::cout << "array[" << i << "] = " << array1[i] << std::endl;
		std::cout << std::endl;
	}
    std::cout << "------- CASE 3: ---- test out of bound index error ---------------------" << std::endl;
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