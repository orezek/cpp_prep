/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:45:40 by mbartos           #+#    #+#             */
/*   Updated: 2024/07/24 14:25:57 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

Base::~Base () {};

Base* generate(void)
{
	Base * basePtr;

	srand(time(0));
	int randomValue = rand();

	switch (randomValue % 3)
	{
		case 0:
			basePtr = new A();
			break ;
		case 1:
			basePtr = new B();
			break ;
		case 2:
			basePtr = new C();
			break ;
		default:
			basePtr = NULL;
	}
	return (basePtr);
};

// In C++98, dynamic_cast is used for safe downcasting, that is, converting a pointer
// or reference to a base class to a pointer or reference to a derived class. 
// This type of cast is primarily used in the context of polymorphism when 
// you have a base class pointer or reference and you need to determine whether 
// it actually points to an object of a derived class.

void identify(Base* p)
{
	if (dynamic_cast<A*>(p) != NULL)
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p) != NULL)
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p) != NULL)
		std::cout << "C" << std::endl;
	else
		std::cout << "Not A, nor B, nor C." << std::endl;
};

void identify(Base& p)
{
	try
	{
		A& refA = dynamic_cast<A&>(p);
		(void) refA;
		std::cout << "A" << std::endl;
	}
	catch(const std::exception& e) {}

	try
	{
		B& refB = dynamic_cast<B&>(p);
		(void) refB;
		std::cout << "B" << std::endl;
	}
	catch(const std::exception& e) {}

	try
	{
		C& refC = dynamic_cast<C&>(p);
		(void) refC;
		std::cout << "C" << std::endl;
	}
	catch(const std::exception& e) {}
};