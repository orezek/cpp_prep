/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:31:32 by mbartos           #+#    #+#             */
/*   Updated: 2024/07/24 10:11:46 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ScalarConverter.hpp"
int	main(int argc, const char** argv)
{
	try
	{
		if (argc == 2)
			ScalarConverter::convert(std::string (argv[1]));
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return (0); // delete if you want to see all the tests
	
	std::cout << "---------------------------------" << std::endl;

	try
	{
		std::string test;
		std::cout << "------------ INT ------------" << std::endl;
		//random int
		test = "42";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);

		std::cout << "--------------" << std::endl << std::endl;
		//random negative int
		test = "-42";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);

		std::cout << "--------------" << std::endl << std::endl;		std::cout << "--------- MIN/MAX INT ---------" << std::endl;

		//max_int
		test = "2147483647";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);

		std::cout << "--------------" << std::endl << std::endl;
		//min_int
		test = "-2147483648";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;

		std::cout << "------ SPECIAL CHARACTERS ------" << std::endl;
		// -inf
		test = "-inf";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;

		// +inf
		test = "+inf";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;

		// nan
		test = "nan";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;

		std::cout << "------------ CHAR ------------" << std::endl;
		// char
		test = "a";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);

		std::cout << "--------------" << std::endl << std::endl;
		// non-printable char from int
		test = "2";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;

		std::cout << "------------ FLOAT ------------" << std::endl;
		// float1
		test = "2.1f";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;

		// float2
		test = "42.f";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;

		// negative float3
		test = "-42.f";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;


		std::cout << "------------ DOUBLE ------------" << std::endl;
		// double1
		test = "2.1";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;

		// double2
		test = "42.";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;

		// negative double3
		test = "-42.";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	try
	{
		std::string test;
		std::cout << "--------- MAX INT+1 ---------" << std::endl;
		//max_int + 1
		test = "2147483648";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << std::endl;
	try
	{
		std::string test;
		std::cout << "--------- MIN INT-1 ---------" << std::endl;
		//min_int - 1
		test = "-2147483649";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	

	return (0);
}