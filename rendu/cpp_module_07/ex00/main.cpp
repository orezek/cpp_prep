#include "whatever.hpp"

/*
Type agnostic code that does not need to be handcoded for each new data.
 */


int main()
{
	{
		std::cout << "" << std::endl;
        std::cout << "CASE: 1 - integers \" a = 2 \" and \" b = 3\" " << std::endl;
		int a = 2;
		int b = 3;
        std::cout << "Swapping \"a\" for \"b\"" << std::endl;
		::swap( a, b );
		std::cout << "a = " << a << ", b = " << b << std::endl;
		std::cout << "------------------------------" << std::endl;
        std::cout << "MIN and MAX" << std::endl;
		std::cout << "min(a, b ) = " << ::min( a, b ) << std::endl;
		std::cout << "max(a, b ) = " << ::max( a, b ) << std::endl;
		std::cout << "------------------------------" << std::endl;
        std::cout << "CASE: 2 - strings \"c\" and \"d\" " << std::endl;
		std::string c = "chaine1";
		std::string d = "chaine2";
		::swap(c, d);
		std::cout << "Swapping \"c = chaine1\" for \"d = chaine2\"" << std::endl;
		std::cout << "c = " << c << ", d = " << d << std::endl;
		std::cout << "min(c, d ) = " << ::min( c, d ) << std::endl;
		std::cout << "max(c, d ) = " << ::max( c, d ) << std::endl;
	}
	std::cout << "------------------------------------------" << std::endl;
	{
        std::cout << "CASE: 3 - double \"a = 5.5\", \"b = 10 \" and \"c  = 5.5\"" << std::endl;
		double a = 5.5;
		double b = 10;

		std::cout << "Min of a = " << a << " and b = " << b << " is: " << min(a, b) << std::endl;
		std::cout << "Max of a = " << a << " and b = " << b << " is: " << max(a, b) << std::endl;

		double c = 5.5;
		std::cout << "MIN and MAX" << std::endl;
		std::cout << "Min of a = " << a << " and c = " << c << " is: " << min(a, c) << std::endl;
		std::cout << "Max of a = " << a << " and c = " << c << " is: " << max(a, c) << std::endl;
		std::cout << "Swapping \"a\" for \"b\"" << std::endl;
		std::cout << "Before swap: a = " << a << ", b = " << b  << std::endl;
		swap(a, b);
		std::cout << "After swap:  a = " << a << ", b = " << b  << std::endl;

		return (0);
	}
}