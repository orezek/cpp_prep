#include "Span.hpp"
#include <climits>

int	main()
{
	// Intra main
	std::cout << "Intra main: " << std::endl;
	try
	{
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << "\n";
	}

	std::cout << "----------------------------------------------------" << std::endl;

	try
	{
		Span testSpan(10);
		testSpan.addNumber(INT_MIN);
		testSpan.addNumber(INT_MAX);
		testSpan.addNumber(0);
		testSpan.addNumber(10);
		testSpan.addNumber(300);
		testSpan.addNumber(5000);
		testSpan.addNumber(12);
		testSpan.addNumber(299);
		testSpan.addNumber(5003);
		testSpan.addNumber(302);
		std::cout << "Longest span: " << testSpan.longestSpan() << std::endl;
		std::cout << "Shortest span: " << testSpan.shortestSpan() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << "\n";
	}

	std::cout << "----------------------------------------------------" << std::endl;

	try
	{
		Span testSpan2(10000);
		testSpan2.addManyNumbers(10000);
		// testSpan2.printNumbers();
		std::cout << "Longest span: " << testSpan2.longestSpan() << std::endl;
		std::cout << "Shortest span: " << testSpan2.shortestSpan() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << "\n";
	}

	return (0);
}