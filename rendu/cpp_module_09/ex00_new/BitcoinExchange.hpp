// BitcoinExchange.hpp

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
private:
    std::map<std::string, float> _rateData; // Map of date to Bitcoin price on that date
public:
    BitcoinExchange();
    BitcoinExchange(const std::string &dataFile = "data.csv");
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    ~BitcoinExchange();
    // Returns the exchange rate for the given date or the closest previous date
    float getRate(const std::string &date) const;
};

#endif
