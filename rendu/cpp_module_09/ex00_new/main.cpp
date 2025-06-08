// main.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "BitcoinExchange.hpp"

// Helper function to check basic date format "YYYY-MM-DD"
static bool isValidDateFormat(const std::string &date) {
    // A valid date string should have length 10: e.g., "2023-06-07"
    if (date.size() != 10) {
        return false;
    }
    // Check year, month, day positions
    // YYYY (4 digits)
    for (int i = 0; i < 4; ++i) {
        if (!isdigit(date[i])) return false;
    }
    if (date[4] != '-' || date[7] != '-') return false;
    // MM (2 digits)
    if (!isdigit(date[5]) || !isdigit(date[6])) return false;
    // DD (2 digits)
    if (!isdigit(date[8]) || !isdigit(date[9])) return false;
    return true;
}

// Helper function to validate that year-month-day form a real calendar date
static bool isValidDateValue(int year, int month, int day) {
    if (year < 0 || month < 1 || month > 12 || day < 1) {
        return false;
    }
    // Determine days in the given month (account for leap years in February)
    int maxDay;
    switch (month) {
        case 2: // February
            maxDay = 28;
            // Check leap year: divisible by 4 and (not divisible by 100 or divisible by 400)
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                maxDay = 29;
            }
            break;
        case 4: case 6: case 9: case 11:
            maxDay = 30;
            break;
        default:
            maxDay = 31;
    }
    if (day > maxDay) {
        return false;
    }
    return true;
}

int main(int argc, char** argv) {
    // Check for proper usage: one input file argument
    if (argc != 2) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }
    // Try opening the input file
    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    // Check if file is empty
    if (input.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "Error: empty input file." << std::endl;
        return 1;
    }

    // Initialize the BitcoinExchange with the historical data
    BitcoinExchange btc;
    std::string line;
    // Process each line of the input file
    while (std::getline(input, line)) {
        if (line.empty()) {
            // Skip empty lines (no data)
            continue;
        }
        // Trim whitespace around the line
        size_t start = line.find_first_not_of(" \t\f\v\r");
        size_t end = line.find_last_not_of(" \t\f\v\r");
        std::string trimmed = (start == std::string::npos) ? "" : line.substr(start, end - start + 1);
        if (trimmed.empty()) {
            continue;
        }
        // Ignore a header line (e.g., "date | value") if present
        if (trimmed == "date | value") {
            continue;
        }
        // Each valid line should contain a '|' separator between date and value
        size_t pipePos = trimmed.find('|');
        if (pipePos == std::string::npos) {
            std::cout << "Error: bad input => " << trimmed << std::endl;
            continue;
        }
        std::string dateStr = trimmed.substr(0, pipePos);
        std::string valueStr = trimmed.substr(pipePos + 1);
        // Remove whitespace around date and value substrings
        if (!dateStr.empty() && dateStr[dateStr.size()-1] == ' ')
            dateStr = dateStr.substr(0, dateStr.find_last_not_of(" ") + 1);
        if (!dateStr.empty() && dateStr[0] == ' ')
            dateStr = dateStr.substr(dateStr.find_first_not_of(" "));
        if (!valueStr.empty() && valueStr[0] == ' ')
            valueStr = valueStr.substr(valueStr.find_first_not_of(" "));
        if (!valueStr.empty() && valueStr[valueStr.size()-1] == ' ')
            valueStr = valueStr.substr(0, valueStr.find_last_not_of(" ") + 1);
        // Validate date format and logical date values
        if (!isValidDateFormat(dateStr)) {
            std::cout << "Error: bad input => " << trimmed << std::endl;
            continue;
        }
        int year = std::atoi(dateStr.substr(0,4).c_str());
        int month = std::atoi(dateStr.substr(5,2).c_str());
        int day = std::atoi(dateStr.substr(8,2).c_str());
        if (!isValidDateValue(year, month, day)) {
            std::cout << "Error: bad input => " << trimmed << std::endl;
            continue;
        }
        // Validate the numeric value
        if (valueStr.empty()) {
            std::cout << "Error: bad input => " << trimmed << std::endl;
            continue;
        }
        // Check if value is negative (starts with '-')
        if (valueStr[0] == '-') {
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        }
        // Parse the value as a floating-point number (using strtod for C++98 compatibility)
        char* endPtr = NULL;
        errno = 0;                          // 1) reset before strtod

        double value = std::strtod(valueStr.c_str(), &endPtr);

        /*--- extra validation ----------------------------------------------------*/
        bool notNumber   = (value != value);                     // NaN is the only value where x != x
        bool isInfinity  = (value == HUGE_VAL || value == -HUGE_VAL);
        bool overFlow    = (errno == ERANGE);                    // strtod overflow/underflow
        /*-------------------------------------------------------------------------*/

        if (endPtr == valueStr.c_str() || *endPtr != '\0' || notNumber || isInfinity || overFlow) {
            std::cout << "Error: bad input => " << trimmed << std::endl;
            continue;
        }
        if (value < 0.0) {
            // Negative values (shouldn't happen due to earlier check)
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        }
        if (value > 1000.0) {
            std::cout << "Error: too large a number." << std::endl;
            continue;
        }
        // At this point, we have a valid date and value.
        // Retrieve the exchange rate for the given date (or nearest prior date)
        try {
            float rate = btc.getRate(dateStr);
            double result = rate * value;
            // Format output showing two decimal places for the result
            std::ostringstream oss;
            oss.setf(std::ios::fixed);
            oss.precision(2);
            oss << result;
            std::string resultStr = oss.str();
            // Print the result in the required format: "YYYY-MM-DD => value = converted_value"
            // Use numeric output for value (this will drop any trailing decimal .0 for integers)
            std::ostringstream vs;
            vs << value;
            std::string valueOut = vs.str();
            std::cout << dateStr << " => " << valueOut << " = " << resultStr << std::endl;
        } catch (const std::out_of_range&) {
            // If the date is before the earliest data available, treat as bad input
            std::cout << "Error: bad input - no earlier date available => " << trimmed << std::endl;
        }
    }
    return 0;
}
