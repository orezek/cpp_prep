#ifndef PMERGEME_HPP
#define PMERGEME_HPP

/* ************************************************************************** */
/*                                                                            */
/*        PmergeMe — Ford-Johnson “merge-insert” sorter                       */
/*        Complies with Orthodox Canonical Form (OCF)                         */
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
    /*------------- Core algorithm (templated) ----------*/
    template <typename C>
    static void fordJohnsonSort(C& data)
    {
        typedef typename C::value_type value_type;
        const std::size_t n = data.size();
        if (n < 2) return;

        const std::size_t pairCnt  = n / 2;
        const bool        leftover = (n % 2);
        value_type tailVal = value_type();

        /* Split into large / small halves per pair */
        std::vector<value_type> large; large.reserve(pairCnt);
        std::vector<value_type> small; small.reserve(pairCnt);

        for (std::size_t i = 0; i < pairCnt; ++i)
        {
            std::size_t i1 = 2 * i;
            std::size_t i2 = i1 + 1;

            if (data[i1] < data[i2])
            {   large.push_back(data[i2]);  small.push_back(data[i1]); }
            else
            {   large.push_back(data[i1]);  small.push_back(data[i2]); }
        }
        if (leftover) tailVal = data.back();

        /* Recursively sort the ‘large’ list (becomes main chain) */
        C mainChain;
        mainChain.assign(large.begin(), large.end());
        fordJohnsonSort(mainChain);

        /* Insert buddy of smallest element in main chain */
        if (!mainChain.empty())
        {
            const value_type smallestLarge = mainChain.front();
            std::size_t idx = 0;
            for (; idx < large.size(); ++idx)
                if (large[idx] == smallestLarge) break;

            if (idx < small.size())
            {
                mainChain.insert(mainChain.begin(), small[idx]);
                small.erase(small.begin() + idx);
            }
        }

        /* Gather remaining pend elements, sort, then insert */
        std::vector<value_type> pend;
        pend.reserve(small.size() + (leftover ? 1 : 0));
        pend.insert(pend.end(), small.begin(), small.end());
        if (leftover) pend.push_back(tailVal);
        std::sort(pend.begin(), pend.end());

        for (std::size_t p = 0; p < pend.size(); ++p)
        {
            typename C::iterator pos =
                    std::lower_bound(mainChain.begin(), mainChain.end(), pend[p]);
            mainChain.insert(pos, pend[p]);
        }
        data.assign(mainChain.begin(), mainChain.end());
    }
};

#endif /* PMERGEME_HPP */
