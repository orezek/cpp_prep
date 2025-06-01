/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:35:52 by mbartos           #+#    #+#             */
/*   Updated: 2024/08/30 10:28:09 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <string>
#include <cstdlib>

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange&);
		BitcoinExchange& operator=(const BitcoinExchange&);
		~BitcoinExchange();

		int LoadDB();
		void printDatabase(); // for checking
		int LoadInput(const std::string inputFileName);

		class MissingHeader : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

	private:
		std::map<std::string, double> database;
		std::map<std::string, int> daysInMonths;

		void LoadDaysInMonths();
		std::ifstream* LoadFile(const std::string filename);
		int CheckHeader(std::ifstream& fin);
		int CheckLine(std::string line);
		int CheckDate(std::string line);
		int CheckValue(std::string value);
		void FindAndPrint(std::string date, std::string value);
};

std::string trim(const std::string& line);

#endif