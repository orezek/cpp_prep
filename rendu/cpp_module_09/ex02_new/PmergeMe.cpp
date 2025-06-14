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


/*------------- fordJohnsonSort for std::vector<int> ---------------------*/
void PmergeMe::fordJohnsonSort(std::vector<int>& data)
{
    const std::size_t n = data.size();
    if (n < 2) return;

    const std::size_t pairCnt  = n / 2;
    const bool        leftover = (n & 1) != 0;
    int tailVal = 0;

    std::vector<Pair> pairs;  pairs.reserve(pairCnt);
    for (std::size_t i = 0; i < pairCnt; ++i) {
        int a = data[2 * i];
        int b = data[2 * i + 1];
        if (a < b) pairs.push_back(Pair(b, a));
        else       pairs.push_back(Pair(a, b));
    }
    if (leftover) tailVal = data.back();

    /* sort pairs by their “max” component */
    std::sort(pairs.begin(), pairs.end());

    std::vector<int> mainChain;  mainChain.reserve(pairCnt + leftover);
    std::vector<int> pend;       pend.reserve(pairCnt - 1 + leftover);

    for (std::size_t i = 0; i < pairs.size(); ++i) {
        mainChain.push_back(pairs[i].max);
        if (i == 0) continue;            // B₀ handled later
        pend.push_back(pairs[i].min);
    }
    mainChain.insert(mainChain.begin(), pairs[0].min);   // B₀
    if (leftover) pend.push_back(tailVal);

    std::vector<std::size_t> schedule;
    makeJacobOrder(pend.size(), schedule);

    for (std::size_t k = 0; k < schedule.size(); ++k) {
        int val = pend[schedule[k]];
        std::vector<int>::iterator pos =
            std::lower_bound(mainChain.begin(), mainChain.end(), val);
        mainChain.insert(pos, val);
    }

    data.assign(mainChain.begin(), mainChain.end());
}

/*------------- fordJohnsonSort for std::deque<int> ----------------------*/
void PmergeMe::fordJohnsonSort(std::deque<int>& data)
{
    const std::size_t n = data.size();
    if (n < 2) return;

    const std::size_t pairCnt  = n / 2;
    const bool        leftover = (n & 1) != 0;
    int tailVal = 0;

    std::vector<Pair> pairs;  pairs.reserve(pairCnt);    // still cheaper
    for (std::size_t i = 0; i < pairCnt; ++i) {
        int a = data[2 * i];
        int b = data[2 * i + 1];
        if (a < b) pairs.push_back(Pair(b, a));
        else       pairs.push_back(Pair(a, b));
    }
    if (leftover) tailVal = data.back();

    std::sort(pairs.begin(), pairs.end());

    std::deque<int> mainChain;
    std::vector<int> pend;      pend.reserve(pairCnt - 1 + leftover);

    for (std::size_t i = 0; i < pairs.size(); ++i) {
        mainChain.push_back(pairs[i].max);
        if (i == 0) continue;
        pend.push_back(pairs[i].min);
    }
    mainChain.push_front(pairs[0].min);       // B₀
    if (leftover) pend.push_back(tailVal);

    std::vector<std::size_t> schedule;
    makeJacobOrder(pend.size(), schedule);

    for (std::size_t k = 0; k < schedule.size(); ++k) {
        int val = pend[schedule[k]];
        std::deque<int>::iterator pos =
            std::lower_bound(mainChain.begin(), mainChain.end(), val);
        mainChain.insert(pos, val);
    }

    data.assign(mainChain.begin(), mainChain.end());
}