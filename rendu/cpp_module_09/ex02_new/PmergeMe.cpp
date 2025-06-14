#include "PmergeMe.hpp"
#include <algorithm>   // lower_bound
#include <iterator>    // iterator traits
#include <vector>
#include <deque>

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe&) {}
PmergeMe& PmergeMe::operator=(const PmergeMe&) { return *this; }
PmergeMe::~PmergeMe() {}


void PmergeMe::sort(std::vector<int>& v)
{
    fordJohnsonSort(v);
}

void PmergeMe::sort(std::deque<int>& d)
{
    fordJohnsonSort(d);
}


std::size_t PmergeMe::jacobsthal(std::size_t k)
{
    /*  J(0)=0, J(1)=1, J(n)=J(n-1)+2·J(n-2)  */
    if (k == 0) return 0;
    if (k == 1) return 1;

    std::size_t a = 0;          // J(n-2)
    std::size_t b = 1;          // J(n-1)
    for (std::size_t i = 2; i <= k; ++i)
    {
        std::size_t next = b + 2 * a;
        a = b;
        b = next;
    }
    return b;
}

void PmergeMe::makeJacobOrder(std::size_t p, std::vector<std::size_t>& order)
{
    /*  Builds the 0-based insertion order for p pend elements:
        groups delimited by successive Jacobsthal numbers, each
        group traversed high→low.  */
    order.clear();
    if (p == 0) return;

    std::size_t prev = 0;           // J(k-1)
    std::size_t k    = 1;           // start with J(1)=1

    while (true)
    {
        std::size_t Jk = jacobsthal(k);
        if (Jk >= p)
        {
            Jk = p;                 // last (possibly partial) group
            for (std::size_t i = Jk; i > prev; --i)
                order.push_back(i - 1);   // 0-based
            break;
        }
        for (std::size_t i = Jk; i > prev; --i)
            order.push_back(i - 1);       // 0-based
        prev = Jk;
        ++k;
    }
}
