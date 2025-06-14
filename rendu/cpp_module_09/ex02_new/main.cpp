#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <cstdlib>
#include <cctype>
#include <climits>
#include <sys/time.h>
#include "PmergeMe.hpp"

/*------------------------------------------------------------*
 *  Parse one CLI token → positive int  - with error details  *
 *------------------------------------------------------------*/
static bool  parsePositiveInt(const std::string& s, int& value,
                              std::string& err)
{
    if (s.empty())                { err = "empty argument";           return false; }

    std::size_t i = 0;
    if (s[0] == '+') ++i;
    else if (s[0] == '-')         { err = "negative value \"" + s + '"'; return false; }

    if (i == s.size())            { err = "missing digits in \"" + s + '"'; return false; }

    for ( ; i < s.size(); ++i)
        if (!std::isdigit(static_cast<unsigned char>(s[i])))
        {   err = "non-digit character in \"" + s + '"';  return false; }

    char* end = NULL;
    long v = std::strtol(s.c_str(), &end, 10);
    if (*end != '\0')             { err = "parse failure for \"" + s + '"';   return false; }
    if (v == 0)                   { err = "zero is not positive";             return false; }
    if (v < 0)                    { err = "negative overflow for \"" + s + '"'; return false; }
    if (v > INT_MAX)              { err = "value out of range in \"" + s + '"'; return false; }

    value = static_cast<int>(v);
    return true;
}

/*------------------------------------------------------------*
 *  main program                                              *
 *------------------------------------------------------------*/
int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Error: no numbers supplied" << std::endl;
        return 1;
    }

    std::vector<int> vec;
    std::deque<int>  deq;
    vec.reserve(argc - 1);

    for (int a = 1; a < argc; ++a)
    {
        int val;  std::string why;
        if (!parsePositiveInt(argv[a], val, why))
        {
            std::cerr << "Error: " << why << std::endl;
            return 1;
        }
        vec.push_back(val);
        deq.push_back(val);
    }

    std::vector<int> before(vec);             // snapshot of original order

    /*---- timed Ford-Johnson on std::vector ----*/
    timeval t0, t1;
    gettimeofday(&t0, NULL);
    PmergeMe::sort(vec);
    gettimeofday(&t1, NULL);
    long vecUs = (t1.tv_sec - t0.tv_sec) * 1000000L + (t1.tv_usec - t0.tv_usec);

    /*---- timed Ford-Johnson on std::deque  ----*/
    gettimeofday(&t0, NULL);
    PmergeMe::sort(deq);
    gettimeofday(&t1, NULL);
    long deqUs = (t1.tv_sec - t0.tv_sec) * 1000000L + (t1.tv_usec - t0.tv_usec);

    /*---- output phase ----*/
    std::cout << "Before: ";
    for (std::size_t i = 0; i < before.size(); ++i)
    {
        std::cout << before[i];
        if (i + 1 < before.size()) std::cout << ' ';
    }
    std::cout << std::endl;

    std::cout << "After:  ";
    for (std::size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i];
        if (i + 1 < vec.size()) std::cout << ' ';
    }
    std::cout << std::endl;

    std::cout << "Time to process a range of "
              << vec.size() << " elements with std::vector : "
              << vecUs << " us" << std::endl;

    std::cout << "Time to process a range of "
              << deq.size() << " elements with std::deque  : "
              << deqUs << " us" << std::endl;

    return 0;
}
