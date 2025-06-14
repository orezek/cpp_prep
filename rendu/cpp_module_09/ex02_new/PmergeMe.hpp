#ifndef PMERGEME_HPP
#define PMERGEME_HPP

/* ************************************************************************** */
/*                                                                            */
/*        PmergeMe — Ford-Johnson “merge-insert” sorter                        */
/*        C++98, header-only implementation                                   */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>
#include <cstddef>      // std::size_t

class PmergeMe
{
public:
    /*------------- Orthodox Canonical Form -------------*/
    PmergeMe();                                   // default constructor
    PmergeMe(const PmergeMe& other);              // copy constructor
    PmergeMe& operator=(const PmergeMe& other);   // copy assignment
    ~PmergeMe();                                  // destructor

    /*------------- Public interface --------------------*/
    static void sort(std::vector<int>& v);        // wrappers in .cpp
    static void sort(std::deque<int>&  d);

private:
    /* ------------------ Jacobsthal helpers ------------------------------- */
    static std::size_t jacobsthal(std::size_t k);
    static void makeJacobOrder(std::size_t p, std::vector<std::size_t>& order);

    /*------------- Ford-Johnson – generic container ----------------------- */
    template <typename C> static void fordJohnsonSort(C& data)
    {
        typedef typename C::value_type value_type;
        const std::size_t n = data.size();
        if (n < 2) return;

        /* ---- 1. Split into pairs --------------------------------------- */
        const std::size_t pairCnt  = n / 2;
        const bool        leftover = (n % 2) != 0;
        value_type        tailVal  = value_type();          // for an odd count

        std::vector< value_type > large;  large.reserve(pairCnt);
        std::vector< value_type > small;  small.reserve(pairCnt);

        for (std::size_t i = 0; i < pairCnt; ++i)
        {
            const value_type& a = data[2 * i];
            const value_type& b = data[2 * i + 1];

            if (a < b)      { large.push_back(b);  small.push_back(a); }
            else            { large.push_back(a);  small.push_back(b); }
        }
        if (leftover) tailVal = data.back();

        /* ---- 2. Recursively sort the “large” list ---------------------- */
        fordJohnsonSort(large);

        C mainChain;
        mainChain.assign(large.begin(), large.end());   // sorted “A” elements

        /* ---- 3. Insert the buddy of the very first pair (B₀) ----------- */
        mainChain.insert(mainChain.begin(), small[0]);

        /* ---- 4. Collect remaining pend elements ------------------------ */
        std::vector< value_type > pend;
        pend.reserve(pairCnt - 1 + (leftover ? 1 : 0));

        for (std::size_t i = 1; i < small.size(); ++i)      // B₁ … B_{m-1}
            pend.push_back(small[i]);
        if (leftover)                                        // possible tail
            pend.push_back(tailVal);

        /* ---- 5. Jacobsthal insertion schedule -------------------------- */
        std::vector< std::size_t > schedule;
        makeJacobOrder(pend.size(), schedule);

        /* ---- 6. Insert pend elements in scheduled order ---------------- */
        for (std::size_t s = 0; s < schedule.size(); ++s)
        {
            const value_type val = pend[ schedule[s] ];

            typename C::iterator pos =
                std::lower_bound(mainChain.begin(), mainChain.end(), val);

            mainChain.insert(pos, val);
        }

        /* ---- 7. Copy result back out ----------------------------------- */
        data.assign(mainChain.begin(), mainChain.end());
    }
};

#endif /* PMERGEME_HPP */