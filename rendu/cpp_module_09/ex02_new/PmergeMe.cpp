#include "PmergeMe.hpp"

/* ************************************************************************** */
/*                       Orthodox Canonical Form                              */
/* ************************************************************************** */

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe&) {}
PmergeMe& PmergeMe::operator=(const PmergeMe&) { return *this; }
PmergeMe::~PmergeMe() {}

/* ************************************************************************** */
/*                       Public sort wrappers                                 */
/* ************************************************************************** */

void PmergeMe::sort(std::vector<int>& v)
{
    fordJohnsonSort(v);
}

void PmergeMe::sort(std::deque<int>& d)
{
    fordJohnsonSort(d);
}
