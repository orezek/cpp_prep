#include <iostream>
#include "RPN.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Incorrect input." << std::endl;
		return (1);
	}

	try
	{
		RPN rpn;
		rpn.Calculate(argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
	}

	return (0);
}
