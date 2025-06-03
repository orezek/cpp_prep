#include "Base.hpp"

int	main ()
{

    std::cout << "Test CASE: 1" << std::endl;
	Base* basePtr;

	basePtr = generate();
	std::cout << "Identify class by pointer: " << std::endl;
	identify(basePtr);
	std::cout << "Identify class by reference: " << std::endl;
	identify(*basePtr);
	delete basePtr;

	return (0);
}