/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:21:37 by mbartos           #+#    #+#             */
/*   Updated: 2024/08/07 18:24:47 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Incorrect input." << std::endl;
		return (1);
	}

	BitcoinExchange btcEx;
	const std::string filename = argv[1];
	try
	{
		btcEx.LoadDB();
		btcEx.LoadInput(filename);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (99);
	}
	return (0);
}


// #include <gtest/gtest.h>
// #include <iostream>
// #include <sstream>
// #include <string>

// char* g_input_file;

// std::string ReadFile(const std::string& file_path) {
//     std::ifstream file(file_path);
//     if (!file.is_open()) {
//         return "";
//     }
//     std::ostringstream oss;
//     oss << file.rdbuf();
//     return oss.str();
// }

// // Test cases
// TEST(inputTXT, Test1) {
//     std::ostringstream oss;
//     std::streambuf* p_cout_buf = std::cout.rdbuf();

//     std::cout.rdbuf(oss.rdbuf());

//     std::cout.rdbuf(p_cout_buf);

//     EXPECT_EQ(oss.str(), "\n");
// }

// TEST(leapTXT, Test2) {
//     std::ostringstream oss;
//     std::streambuf* p_cout_buf = std::cout.rdbuf();

//     std::cout.rdbuf(oss.rdbuf());

// 	BitcoinExchange btcEx;
// 	btcEx.LoadDB();
// 	btcEx.LoadInput(g_input_file);

//     std::cout.rdbuf(p_cout_buf);

//     std::string expected_output = ReadFile("leapRESULT.txt");
//     EXPECT_EQ(oss.str(), expected_output);
// }


// int main(int argc, char **argv)
// {
// 	::testing::InitGoogleTest(&argc, argv);

// 	if (argc > 1)
// 	{
// 		std::string arg = argv[1];
//  		g_input_file = argv[1];
// 		if (arg == "input.txt") {
// 			// Run only tests in TestSuite1
// 			::testing::GTEST_FLAG(filter) = "InputTXT.*";
// 		} else if (arg == "leap.txt") {
// 			// Run only tests in TestSuite2
// 			::testing::GTEST_FLAG(filter) = "leapTXT.*";
// 		}
// 	}
// 	return RUN_ALL_TESTS();
// }
 