#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& refObj) { *this = refObj; }
const ScalarConverter& ScalarConverter::operator=(const ScalarConverter& refObj) { (void)refObj; return (*this); };
ScalarConverter::~ScalarConverter() {}

bool	ScalarConverter::isChar(const std::string str)
{
	if (!isdigit(static_cast<unsigned char>(str[0])) && str.size() == 1)
		return (true);
	return (false);
}

bool	ScalarConverter::isSpecial(const std::string str)
{
	if (str == "-inff" || str == "+inff" ||
		str == "-inf" || str == "+inf" ||
		str == "nan" || str == "nanf")
		return (true);
	return (false);
}

bool	ScalarConverter::isInt(const std::string str)
{
	std::string::size_type i;

	if (str[0] == '+' || str[0] == '-')
		i = 1;
	else
		i = 0;
	for (; i < str.size(); i++)
	{
		if (!isdigit(static_cast<unsigned char>(str[i])))
			return (false);
	}
	return (true);
}

bool	ScalarConverter::isFloat(const std::string str)
{
	std::string::size_type i;

	if (str.size() < 2)
		return (false);
	if (str[0] == '+' || str[0] == '-')
		i = 1;
	else
		i = 0;
	for(; i < str.size() - 1; i++)
	{
		if (!isdigit(static_cast<unsigned char>(str[i])) && str[i] != '.')
			return (false);
	}
	if (str[str.size() - 1] == 'f' && str.find_first_of("f") == str.find_last_of("f")
			&& str.find_first_of(".") == str.find_last_of(".") && str.find_first_of(".") != std::string::npos)
		return (true);
	return (false);
}

bool	ScalarConverter::isDouble(const std::string str)
{
	std::string::size_type i;

	if (str.size() < 2)
		return (false);
	if (str[0] == '+' || str[0] == '-')
		i = 1;
	else
		i = 0;
	if (StringUtils::digitsAndOneDotOnly(&str[i]))
		return (true);
	return (false);
}

int	ScalarConverter::determineType(const std::string input)
{
	if (input.empty())
		return (ERROR);
	else if (isSpecial(input))
		return (SPECIAL);
	else if(isChar(input))
		return (CHAR);
	else if(isInt(input))
		return (INT);
	else if(isFloat(input))
		return (FLOAT);
	else if(isDouble(input))
		return (DOUBLE);
	return (ERROR);
}

const char *ScalarConverter::invalidInputException::what(void) const throw() 
{
	return ("Invalid input. Only CHAR, INT, FLOAT or DOUBLE are valid.");
}

void	ScalarConverter::castFromChar(values& values, const std::string string)
{
	values.character = static_cast<unsigned char>(string[0]);
	values.int_num = static_cast<long long>(values.character);
	values.double_num = static_cast<double>(values.character);
	values.float_num = static_cast<float>(values.character);
}

void	ScalarConverter::castFromInt(values& values, const std::string string)
{
	values.int_num = std::atoll(string.c_str());
	if (values.int_num >= static_cast<long long>(std::numeric_limits<int>::min()) && values.int_num <= static_cast<long long>(std::numeric_limits<int>::max()))
	{
		values.character = static_cast<unsigned char>(values.int_num);
		values.double_num = static_cast<double>(values.int_num);
		values.float_num = static_cast<float>(values.int_num);
	}
	else
		throw invalidInputException();
}

void	ScalarConverter::castFromDouble(values& values, const std::string string)
{
	values.double_num = std::strtod(string.c_str(), NULL);
	values.character = static_cast<unsigned char>(values.double_num);
	values.int_num = static_cast<long long>(values.double_num);
	values.float_num = static_cast<float>(values.double_num);
}

void	ScalarConverter::castFromFloat(values& values, const std::string string)
{
	values.float_num = std::strtof(string.c_str(), NULL);
	values.character = static_cast<unsigned char>(values.float_num);
	values.int_num = static_cast<long long>(values.float_num);
	values.double_num = static_cast<double>(values.float_num);
}

void	ScalarConverter::printChar(values& values)
{
	if (values.type_of_conversion != CHAR)
	{
		if (values.int_num >= static_cast<long long>(std::numeric_limits<unsigned char>::min()) 
			&& values.int_num <= static_cast<long long>(std::numeric_limits<unsigned char>::max()))
		{
			if (isprint(values.character))
				std::cout << "char: " << values.character << std::endl;
			else
				std::cout << "char: Non displayable" << std::endl; 
		}
		else
			std::cout << "char: impossible" << std::endl;
	}
	else
		std::cout << "char: " << values.character << std::endl;
}

void	ScalarConverter::printInt(values& values)
{
	if (values.int_num >= static_cast<long long>(std::numeric_limits<int>::min()) && values.int_num <= static_cast<long long>(std::numeric_limits<int>::max()))
		std::cout << "int: " << values.int_num << std::endl;
	else
		std::cout << "int: impossible" << std::endl;
}

void	ScalarConverter::printFloat(values& values)
{
		std::cout << "float: " << std::fixed << std::setprecision(PRECISION) << values.float_num << "f" << std::endl;
}

void	ScalarConverter::printDouble(values& values)
{
		std::cout << "double: " << std::fixed << std::setprecision(PRECISION) << values.double_num << std::endl;
}

void	ScalarConverter::printOutput(values& values)
{
	ScalarConverter::printChar(values);
	ScalarConverter::printInt(values);
	ScalarConverter::printFloat(values);
	ScalarConverter::printDouble(values);
}

void	ScalarConverter::printSpecial(const std::string &string, values& values)
{
	if (string == "nan" || string == "nanf")
	{
		values.float_num = std::numeric_limits<float>::quiet_NaN();
		values.double_num = std::numeric_limits<double>::quiet_NaN();
	}
	else if (string == "+inf" || string == "+inff")
	{
		values.float_num = std::numeric_limits<float>::infinity();
		values.double_num = std::numeric_limits<double>::infinity();
	}
	else if (string == "-inf" || string == "-inff")
	{
		values.float_num = static_cast<float>(std::numeric_limits<float>::infinity() * -1);
		values.double_num = static_cast<double>(std::numeric_limits<double>::infinity() * -1);
	}
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: " << values.float_num << "f" << std::endl;
	std::cout << "double: " << values.double_num << std::endl;
}


void	ScalarConverter::convert(const std::string input)
{
	int type;
	values values;

	values.type_of_conversion = determineType(input);
	type = values.type_of_conversion;
	if (type != ERROR)
	{
		if (type == CHAR)
			ScalarConverter::castFromChar(values, input);
		else if (type == INT)
			ScalarConverter::castFromInt(values, input);
		else if (type == DOUBLE)
			ScalarConverter::castFromDouble(values, input);
		else if (type == FLOAT)
			ScalarConverter::castFromFloat(values, input);
		else if (type == SPECIAL)
		{
			printSpecial(input, values);
			return ;
		}
		ScalarConverter::printOutput(values);
	}
	else
		throw invalidInputException();
}