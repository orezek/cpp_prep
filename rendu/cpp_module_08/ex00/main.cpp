#include "easyfind.hpp"
#include <vector>
#include <list>
#include <deque>

int	main()
{
	{
		std::vector<int> vec;

		vec.push_back(10);
		vec.push_back(20);
		vec.push_back(30);
		vec.push_back(40);
		vec.push_back(50);

		try
		{
			easyfind(vec, 30); // This will print '3' if the number is found
			easyfind(vec, 60); // This will print nothing if the number is not found
		}
		catch(std::exception& e)
		{
			std::cerr << "Error: " << e.what() << '\n';
		}
	}
	std::cout << "----------------------------------------------------" << std::endl;
	{
		std::list<int> list;

		list.push_back(10);
		list.push_back(20);
		list.push_back(30);
		list.push_back(40);
		list.push_back(50);

		try
		{
			easyfind(list, 30); // This will print '3' if the number is found
			easyfind(list, 60); // This will print nothing if the number is not found
		}
		catch(std::exception& e)
		{
			std::cerr << "Error: " << e.what() << '\n';
		}
	}
	std::cout << "----------------------------------------------------" << std::endl;
	{
		std::deque<int> deque;

		deque.push_back(10);
		deque.push_back(20);
		deque.push_back(30);
		deque.push_back(40);
		deque.push_back(50);

		try
		{
			easyfind(deque, 30); // This will print '3' if the number is found
			easyfind(deque, 60); // This will print nothing if the number is not found
		}
		catch(std::exception& e)
		{
			std::cerr << "Error: " << e.what() << '\n';
		}
	}

	return (0);
}