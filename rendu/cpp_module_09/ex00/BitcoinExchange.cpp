#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	this->LoadDaysInMonths();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& refObj) 
{
	(void) refObj;
	this->LoadDaysInMonths();
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& refObj) { (void) refObj; return (*this); }

BitcoinExchange::~BitcoinExchange() {}

std::string trim(const std::string& line)
{
	const char* WhiteSpace = " \t\v\r\n";
	std::size_t start = line.find_first_not_of(WhiteSpace);
	std::size_t end = line.find_last_not_of(WhiteSpace);
	return line.substr(start, end - start + 1);
}

int BitcoinExchange::LoadDB()
{
	std::ifstream dataCsv("data.csv");
	if (!dataCsv.is_open())
		throw std::runtime_error("Cannot open file: data.csv");

	std::string line;
	std::string	date;
	std::string	value;
	while (std::getline((dataCsv), line))
	{
		if (line == "date,exchange_rate")
			continue ;

		std::stringstream	stream(line);

		std::getline(stream, date, ',');
		std::getline(stream, value);
		database.insert(std::make_pair(date, strtod(value.c_str(), NULL)));
	}
	dataCsv.close();
	return (0);
}

void BitcoinExchange::printDatabase()
{
	for (std::map<std::string, double>::const_iterator it = database.begin(); it != database.end(); it++)
	{
		std::cout << "|" << it->first << "|" << it->second << "|" << std::endl;
	}
}

void BitcoinExchange::LoadDaysInMonths()
{
	daysInMonths.insert(std::make_pair("01", 31));
	daysInMonths.insert(std::make_pair("02", 28));
	daysInMonths.insert(std::make_pair("03", 31));
	daysInMonths.insert(std::make_pair("04", 30));
	daysInMonths.insert(std::make_pair("05", 31));
	daysInMonths.insert(std::make_pair("06", 30));
	daysInMonths.insert(std::make_pair("07", 31));
	daysInMonths.insert(std::make_pair("08", 31));
	daysInMonths.insert(std::make_pair("09", 30));
	daysInMonths.insert(std::make_pair("10", 31));
	daysInMonths.insert(std::make_pair("11", 30));
	daysInMonths.insert(std::make_pair("12", 31));
}

int BitcoinExchange::CheckHeader(std::ifstream& fin)
{
	std::string line;
	std::getline(fin, line);

	std::string date;
	std::string value;
	std::stringstream stream(line);

	std::getline(stream, date, '|');
	date = trim(date);
	std::getline(stream, value);
	value = trim (value);
	if (date != "date" || value != "value")
	{
		throw MissingHeader();
	}
	return (1);
}

int BitcoinExchange::CheckLine(std::string line)
{
	if (line.size() < 12 || line.find_last_of("|") != line.find_first_of("|") || line.find_first_of("|") == std::string::npos)
	{
		std::cout << "Error: Invalid line." << std::endl;
		return (0);
	}
	return (1);
}

int BitcoinExchange::CheckDate(std::string date)
{
	if (date.size() != 10)
	{
		std::cout << "Error: Invalid date." << std::endl;
		return (0);
	}
	if (date[4] != '-' || date[7] != '-')
	{
		std::cout << "Error: Invalid date." << std::endl;
		return (0);
	}
	if (date < "2009-01-02")
	{
		std::cout << "Error: Invalid date." << std::endl;
		return (0);
	}
	int year = std::atoi(date.substr(0,4).c_str());
	std::string month = date.substr(5, 2);
	int day = std::atoi(date.substr(8, 2).c_str());
	// std::cout << year << "-" << month << std::endl;
	std::map<std::string, int>::iterator it = daysInMonths.find(month);
	// leap year?
	if (month == "02" && it != daysInMonths.end())
	{
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		{
			// is leap year
			if (day > (it->second + 1))
			{
				std::cout << "Error: Invalid date." << std::endl;
				return (0);
			}
		}
		else
		{
			// is not leap year;
			if (day > (it->second))
			{
				std::cout << "Error: Invalid date." << std::endl;
				return (0);
			}
		}
	}
	else if (it == daysInMonths.end() || day > it->second)
	{
		std::cout << "Error: Invalid date." << std::endl;
		return (0);
	}

	return (1);
}

int BitcoinExchange::CheckValue(std::string value)
{
	if (value.find_last_of(".") != value.find_first_of("."))
	{
		std::cout << "Error: Invalid value. Multiple dots." << std::endl;
		return (0);
	}
	double	amount = strtod(value.c_str(), NULL);
	if (amount < 0 || amount > 1000)
	{
		std::cout << "Error: Number not in <0, 1000> range." << std::endl;
		return (0);
	}
	return (1);
}

void BitcoinExchange::FindAndPrint(std::string date, std::string value)
{
	double	amount = strtod(value.c_str(), NULL);
	std::map<std::string, double>::const_iterator it = this->database.find(date);
	if (it == this->database.end())
	{
		it = this->database.upper_bound(date);
		if (it != this->database.begin())
			it--;
		else
			std::cout << "Date not found." << std::endl;
	}
	std::cout << date << " => " << amount << " = " << it->second * amount << std::endl;

}

int BitcoinExchange::LoadInput(const std::string inputFileName)
{
	std::ifstream fin(inputFileName.c_str());
	if (!fin.is_open())
		throw std::runtime_error("Cannot open file: " + inputFileName);

	this->CheckHeader(fin);

	std::string line;
	while (std::getline(fin, line))
	{
		if (this->CheckLine(line) == 0)
			continue ;

		std::stringstream stream(line);

		std::string date;
		std::getline(stream, date, '|');
		date = trim(date);
		if (this->CheckDate(date) == 0)
			continue ;

		std::string value;
		std::getline(stream, value);
		value = trim(value);
		if(this->CheckValue(value) == 0)
			continue ;

		this->FindAndPrint(date, value);
	}
	fin.close();
	return (0);
}

const char *BitcoinExchange::MissingHeader::what(void) const throw()
{
	return ("Header is missing. Add it to the file in format \"date | value\"");
}
