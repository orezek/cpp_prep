#include "iter.hpp"

void addTen(int& n) {
  n = n + 10;
}

void addTen(double& n) {
	n = n + 10;
}

void ftToLower(char& c)
{
	c = std::tolower(static_cast<unsigned char>(c));
}

void ftToUpper(char& c)
{
	c = std::toupper(static_cast<unsigned char>(c));
}

int main()
{
	std::cout << "-------- CASE 1: Add 10 to ints in array -------------" << std::endl;
	{
		int arr[3] = {1, 2, 3};

		std::cout << "Before iter:" << std::endl;
		for (std::size_t i = 0; i < 3; i++)
			std::cout << "arr[" << i << "] = " << arr[i] << std::endl;

 		iter(arr, 3, addTen);

		std::cout << std::endl;

		std::cout << "After iter:" << std::endl;
		for (std::size_t i = 0; i < 3; i++)
			std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
	}
	std::cout << "------- CASE 2: Add 10 to doubles in array ------------" << std::endl;
	{
		double arr[3] = {1.123, 2.456, 3.789};

		std::cout << "Before iter:" << std::endl;
		for (std::size_t i = 0; i < 3; i++)
			std::cout << "arr[" << i << "] = " << arr[i] << std::endl;

 		iter(arr, 3, addTen);

		std::cout << std::endl;

		std::cout << "After iter:" << std::endl;
		for (std::size_t i = 0; i < 3; i++)
			std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
	}
	std::cout << "-------CASE 3: Convert to upper case letters ------" << std::endl;
	{
		char arr[18] = "Hello, my friend!";

		std::cout << "Before iter:" << std::endl;
		std::cout << arr << std::endl;

 		iter(arr, 18, ftToUpper);

		std::cout << std::endl;

		std::cout << "After iter:" << std::endl;
		std::cout << arr << std::endl;
	}
	std::cout << "----------------------------------------------------" << std::endl;
	return (0);
}