/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:25:22 by mbartos           #+#    #+#             */
/*   Updated: 2024/07/24 09:59:29 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <cctype>
#include <cstdlib>

#include "StringUtils.hpp"

#define PRECISION 3

class ScalarConverter
{
	private:

		enum type {
			ERROR = -1,
			CHAR = 0,
			INT,
			DOUBLE,
			FLOAT,
			SPECIAL
		};

		struct values {
			unsigned char	character;
			long long		int_num;
			double			double_num;
			float			float_num;
			int				type_of_conversion;
		};

		ScalarConverter();
		ScalarConverter(const ScalarConverter&);
		const ScalarConverter& operator=(const ScalarConverter&);
		~ScalarConverter();

		static int typeChoose(const std::string input);
		static bool isSpecial(const std::string str);
		static bool isChar(const std::string str);
		static bool isInt(const std::string str);
		static bool isFloat(const std::string str);
		static bool isDouble(const std::string str);

		static void	castFromChar(values& values, const std::string string);
		static void	castFromInt(values& values, const std::string string);
		static void	castFromDouble(values& values, const std::string string);
		static void	castFromFloat(values& values, const std::string string);


		static void	printSpecial(const std::string &string, values& values);
		static void printChar(values& values);
		static void printInt(values& values);
		static void printFloat(values& values);
		static void printDouble(values& values);
		static void	printOutput(values& values);

	public:
		static void	convert(const std::string input);

		class invalidInputException : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
};


#endif