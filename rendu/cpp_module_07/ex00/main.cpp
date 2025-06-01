/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:21:37 by mbartos           #+#    #+#             */
/*   Updated: 2024/07/25 11:40:54 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "whatever.hpp"

int main()
{
	{
		int a = 2;
		int b = 3;
		::swap( a, b );
		std::cout << "a = " << a << ", b = " << b << std::endl;
		std::cout << "min(a, b ) = " << ::min( a, b ) << std::endl;
		std::cout << "max(a, b ) = " << ::max( a, b ) << std::endl;
		std::string c = "chaine1";
		std::string d = "chaine2";
		::swap(c, d);
		std::cout << "c = " << c << ", d = " << d << std::endl;
		std::cout << "min(c, d ) = " << ::min( c, d ) << std::endl;
		std::cout << "max(c, d ) = " << ::max( c, d ) << std::endl;
		// return 0;
	}
	std::cout << "------------------------------------------" << std::endl;
	{
		double a = 5.5;
		double b = 10;

		std::cout << "Min of a = " << a << " and b = " << b << " is: " << min(a, b) << std::endl;
		std::cout << "Max of a = " << a << " and b = " << b << " is: " << max(a, b) << std::endl;

		double c = 5.5;
		std::cout << "Min of a = " << a << " and c = " << c << " is: " << min(a, c) << std::endl;
		std::cout << "Max of a = " << a << " and c = " << c << " is: " << max(a, c) << std::endl;

		std::cout << "Before swap: a = " << a << ", b = " << b  << std::endl;
		swap(a, b);
		std::cout << "After swap:  a = " << a << ", b = " << b  << std::endl;

		return (0);
	}
}