#include "Base.hpp"

int	main ()
{
	Base* basePtr;

	basePtr = generate();
	std::cout << "Identify class by pointer: " << std::endl;
	identify(basePtr);
	std::cout << "Identify class by reference: " << std::endl;
	identify(*basePtr);
	delete basePtr;

	return (0);
}