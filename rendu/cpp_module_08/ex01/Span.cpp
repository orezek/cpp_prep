#include "Span.hpp"
#include <ctime>

/*------------- canonical forn ----------------*/
Span::Span() : _maxN(0) {}

Span::Span(unsigned int maxNums) : _maxN(maxNums) {}

Span::Span(const Span& ref) : _maxN(ref._maxN), _numbers(ref._numbers) {}

Span& Span::operator=(const Span& ref)
{
    if (this != &ref)
    {
        this->_maxN   = ref._maxN;
        this->_numbers = ref._numbers;
    }
    return *this;
}

Span::~Span() {}

/*------------- state modifiers ----------------*/
void Span::addNumber(int newNumber)
{
    if (this->_numbers.size() < this->_maxN || this->_maxN == 0)
        this->_numbers.insert(newNumber);
    else
        throw MaxNumbersException();
}

void Span::addMultipleN(int count)           // renamed  ✅
{
    if (this->_numbers.size() == this->_maxN)
        throw MaxNumbersException();

    if (static_cast<unsigned int>(count) + this->_numbers.size() > this->_maxN)
    {
        count = static_cast<int>(this->_maxN - this->_numbers.size());
        std::cout << "Max limit would be exceeded. Only "
                  << count << " random numbers will be added.\n";
    }

    std::vector<int> tmp;
    tmp.reserve(count);

    std::srand(std::time(0));
    for (int i = 0; i < count; ++i)
        tmp.push_back(std::rand());

    this->_numbers.insert(tmp.begin(), tmp.end());
}

/*------------- span queries --------------*/
long int Span::longestSpan()
{
    if (this->_numbers.size() < 2)
        throw NotEnoughNumbersException();

    return std::labs(
        static_cast<long int>(*this->_numbers.rbegin()) -
        static_cast<long int>(*this->_numbers.begin()));
}

long int Span::shortestSpan()
{
    if (this->_numbers.size() < 2)
        throw NotEnoughNumbersException();

    long int diff = LONG_MAX;
    std::multiset<int>::const_iterator it = this->_numbers.begin();
    long int prev = static_cast<long int>(*it);

    for (++it; it != this->_numbers.end(); ++it)
    {
        long int curr = static_cast<long int>(*it);
        long int d = std::labs(curr - prev);
        if (d < diff) diff = d;
        prev = curr;
    }
    return diff;
}

/*------------- helpers / I/O -------------*/
void Span::printInt(int n) { std::cout << n << ", "; }

void Span::printNumbers() const
{
    std::cout << "Numbers: ";
    std::for_each(this->_numbers.begin(), this->_numbers.end(), Span::printInt);
    std::cout << '\n';
}

/*------------- exception text ------------*/
const char* Span::NotEnoughNumbersException::what() const throw()
{
    return "Not enough numbers to compute a span.";
}

const char* Span::MaxNumbersException::what() const throw()
{
    return "Maximum number of elements already reached.";
}
