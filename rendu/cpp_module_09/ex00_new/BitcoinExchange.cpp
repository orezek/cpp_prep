// BitcoinExchange.cpp

#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <stdexcept>

BitcoinExchange::BitcoinExchange(const std::string &dataFile) {
    // Open the provided CSV file containing historical Bitcoin prices
    std::ifstream data(dataFile.c_str());
    if (!data.is_open()) {
        throw std::runtime_error("cannot open database file");
    }
    std::string line;
    // The first line of data.csv might be a header (e.g., "date,price"), skip it
    if (std::getline(data, line)) {
        if (line.find(',') == std::string::npos || !isdigit(line[0])) {
            // If the first line is not data (e.g., contains non-digit start), assume header
        } else {
            // If first line looks like actual data, process it
            std::stringstream ss(line);
            std::string dateStr, priceStr;
            if (std::getline(ss, dateStr, ',') && std::getline(ss, priceStr)) {
                // Trim spaces (if any) around the values
                if (!dateStr.empty() && dateStr[0] == ' ') {
                    dateStr.erase(0, dateStr.find_first_not_of(" "));
                }
                if (!dateStr.empty() && dateStr[dateStr.size()-1] == ' ') {
                    dateStr.erase(dateStr.find_last_not_of(" ") + 1);
                }
                if (!priceStr.empty() && priceStr[0] == ' ') {
                    priceStr.erase(0, priceStr.find_first_not_of(" "));
                }
                if (!priceStr.empty() && priceStr[priceStr.size()-1] == ' ') {
                    priceStr.erase(priceStr.find_last_not_of(" ") + 1);
                }
                float price = static_cast<float>(std::atof(priceStr.c_str()));
                _rateData[dateStr] = price;
            }
        }
    }
    // Read the rest of the lines in the CSV file
    while (std::getline(data, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string dateStr, priceStr;
        if (!std::getline(ss, dateStr, ',') || !std::getline(ss, priceStr)) {
            // Skip lines that don't have both date and price
            continue;
        }
        // Remove whitespace around the date and price fields
        if (!dateStr.empty() && dateStr[0] == ' ') {
            dateStr.erase(0, dateStr.find_first_not_of(" "));
        }
        if (!dateStr.empty() && dateStr[dateStr.size()-1] == ' ') {
            dateStr.erase(dateStr.find_last_not_of(" ") + 1);
        }
        if (!priceStr.empty() && priceStr[0] == ' ') {
            priceStr.erase(0, priceStr.find_first_not_of(" "));
        }
        if (!priceStr.empty() && priceStr[priceStr.size()-1] == ' ') {
            priceStr.erase(priceStr.find_last_not_of(" ") + 1);
        }
        // Convert price string to float and store in the map with the date as key
        float price = static_cast<float>(std::atof(priceStr.c_str()));
        _rateData[dateStr] = price;
    }
    data.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
: _rateData(other._rateData) {
    // Copy constructor (performs shallow copy of map since float and string are value types)
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this != &other) {
        _rateData = other._rateData;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {
    // No dynamic allocation to clean up; relying on RAII
}

float BitcoinExchange::getRate(const std::string &date) const {
    // Find the exchange rate for the given date or nearest earlier date
    // lower_bound returns the first element that is not less than the key
    std::map<std::string, float>::const_iterator it = _rateData.lower_bound(date);
    if (it != _rateData.end() && it->first == date) {
        // Exact date found in database
        return it->second;
    }
    if (it == _rateData.begin()) {
        // The requested date is earlier than the first date in the database
        throw std::out_of_range("No data available for this date or earlier");
    }
    // Otherwise, step back one entry to get the previous date's rate
    --it;
    return it->second;
}
