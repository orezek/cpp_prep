#include <iostream>
#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Incorrect input." << std::endl;
		return (1);
	}

	BitcoinExchange btcEx;
	const std::string filename = argv[1];
	try
	{
		btcEx.LoadDB();
		btcEx.LoadInput(filename);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (99);
	}
	return (0);
}
