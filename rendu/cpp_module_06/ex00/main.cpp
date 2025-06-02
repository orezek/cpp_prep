#include "ScalarConverter.hpp"

/*
The purpose is to understand explicit vs implicit (C-style) casting of numeric strings into specific types.
1) Explicit usage of cast operators.
2) Type detection logic.
3) Error handling and edge case handling.
4) Using static (non-instantiable) class.
*/

int	main(int argc, const char** argv)
{
	try
	{
		if (argc == 2)
			ScalarConverter::convert(std::string(argv[1]));
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	//return (0); // comment out if you want to see all the tests

	std::cout << "Running Test CASES on random string numeric literals." << std::endl;

	try
	{
		std::string test;

		std::cout << "Test CASE 1: Positive INT" << std::endl;
		test = "42";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;

		std::cout << "Test CASE 2: Negative INT" << std::endl;
		test = "-42";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;

		std::cout << "Test CASE 3: MAX INT" << std::endl;
		test = "2147483647";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;

		std::cout << "Test CASE 4: MIN INT" << std::endl;
		test = "-2147483648";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;

		std::cout << "Test CASE 5: SPECIAL -INF" << std::endl;
		test = "-inf";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;

		std::cout << "Test CASE 6: SPECIAL +INF" << std::endl;
		test = "+inf";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;

		std::cout << "Test CASE 7: SPECIAL NAN" << std::endl;
		test = "nan";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;

		std::cout << "Test CASE 8: CHAR LITERAL 'a'" << std::endl;
		test = "a";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;

		std::cout << "Test CASE 9: NON-PRINTABLE CHAR VIA '2'" << std::endl;
		test = "2";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;

		std::cout << "Test CASE 10: FLOAT '2.1f'" << std::endl;
		test = "2.1f";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;

		std::cout << "Test CASE 11: FLOAT '42.f'" << std::endl;
		test = "42.f";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;

		std::cout << "Test CASE 12: NEGATIVE FLOAT '-42.f'" << std::endl;
		test = "-42.f";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;

		std::cout << "Test CASE 13: DOUBLE '2.1'" << std::endl;
		test = "2.1";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;

		std::cout << "Test CASE 14: DOUBLE '42.'" << std::endl;
		test = "42.";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;

		std::cout << "Test CASE 15: NEGATIVE DOUBLE '-42.'" << std::endl;
		test = "-42.";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	try
	{
		std::string test;
		std::cout << "Test CASE 16: MAX INT + 1 (Overflow)" << std::endl;
		test = "2147483648";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	try
	{
		std::cout << "--------------" << std::endl << std::endl;
		std::string test;
		std::cout << "Test CASE 17: MIN INT - 1 (Underflow)" << std::endl;
		test = "-2147483649";
		std::cout << "--------------" << std::endl;
		std::cout << "Trying |" << test << "|:" << std::endl;
		ScalarConverter::convert(test);
		std::cout << "--------------" << std::endl << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

try
{
    std::string test;

    std::cout << "Test CASE 18: INT Zero \"0\"" << std::endl;
    test = "0";
    std::cout << "--------------" << std::endl;
    std::cout << "Trying |" << test << "|:" << std::endl;
    ScalarConverter::convert(test);
    std::cout << "--------------" << std::endl << std::endl;

    std::cout << "Test CASE 19: FLOAT Zero with ‘0.0f’" << std::endl;
    test = "0.0f";
    std::cout << "--------------" << std::endl;
    std::cout << "Trying |" << test << "|:" << std::endl;
    ScalarConverter::convert(test);
    std::cout << "--------------" << std::endl << std::endl;

    std::cout << "Test CASE 20: DOUBLE Zero with ‘0.0’" << std::endl;
    test = "0.0";
    std::cout << "--------------" << std::endl;
    std::cout << "Trying |" << test << "|:" << std::endl;
    ScalarConverter::convert(test);
    std::cout << "--------------" << std::endl << std::endl;

    std::cout << "Test CASE 21: FLOAT pseudo-literal \"nanf\"" << std::endl;
    test = "nanf";
    std::cout << "--------------" << std::endl;
    std::cout << "Trying |" << test << "|:" << std::endl;
    ScalarConverter::convert(test);
    std::cout << "--------------" << std::endl << std::endl;

    std::cout << "Test CASE 22: FLOAT pseudo-literal \"+inff\"" << std::endl;
    test = "+inff";
    std::cout << "--------------" << std::endl;
    std::cout << "Trying |" << test << "|:" << std::endl;
    ScalarConverter::convert(test);
    std::cout << "--------------" << std::endl << std::endl;

    std::cout << "Test CASE 23: FLOAT pseudo-literal \"-inff\"" << std::endl;
    test = "-inff";
    std::cout << "--------------" << std::endl;
    std::cout << "Trying |" << test << "|:" << std::endl;
    ScalarConverter::convert(test);
    std::cout << "--------------" << std::endl << std::endl;

    std::cout << "Test CASE 24: Invalid string \"abc\" (should throw)" << std::endl;
    test = "abc";
    std::cout << "--------------" << std::endl;
    std::cout << "Trying |" << test << "|:" << std::endl;
    ScalarConverter::convert(test);
    std::cout << "--------------" << std::endl << std::endl;
}
catch(const std::exception& e)
{
    std::cerr << e.what() << std::endl;
}


	return (0);
}
