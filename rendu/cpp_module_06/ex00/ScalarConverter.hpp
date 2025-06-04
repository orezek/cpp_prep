#pragma once

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <cctype>
#include <cstdlib>


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

		static int determineType(const std::string input);
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

		// utility
		static bool isDigitAndDot(const std::string str);

	public:
		static void	convert(const std::string input);

		class invalidInputException : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
};
