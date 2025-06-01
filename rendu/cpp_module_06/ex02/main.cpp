/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:57:46 by mbartos           #+#    #+#             */
/*   Updated: 2024/07/24 14:24:38 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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