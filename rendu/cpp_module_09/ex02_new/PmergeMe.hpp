#ifndef PMERGEME_HPP
#define PMERGEME_HPP

/*  PmergeMe – Ford-Johnson “merge-insert” sort
    -------------------------------------------
    Implements the algorithm generically for any random-access STL
    container holding ints.  Public `sort()` overloads are provided
    for std::vector<int> and std::deque<int>; they forward to the
    private templated `fordJohnsonSort()`.

    Only template definitions appear here (allowed by the subject’s
    rules).  Non-template functions are *declared* and defined in
    the translation unit.                                         */

#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>

class PmergeMe {
public:
    // Wrappers defined in main.cpp
    static void sort(std::vector<int>& v);
    static void sort(std::deque<int>& d);

private:
    /*------------------------------------------------------------
     *  Generic Ford-Johnson merge-insert sort
     *-----------------------------------------------------------*/
    template <typename C>
    static void fordJohnsonSort(C& data)
    {
        typedef typename C::value_type value_type;
        const std::size_t n = data.size();
        if (n < 2)
            return;

        const std::size_t pairCnt   = n / 2;
        const bool        leftover  = (n % 2);
        value_type        tailVal   = value_type();

        // Split into “large” and “small” halves per pair
        std::vector<value_type> large;
        std::vector<value_type> small;
        large.reserve(pairCnt);
        small.reserve(pairCnt);

        for (std::size_t i = 0; i < pairCnt; ++i)
        {
            std::size_t i1 = i * 2;
            std::size_t i2 = i1 + 1;

            if (data[i1] < data[i2])
            {
                large.push_back(data[i2]);
                small.push_back(data[i1]);
            }
            else
            {
                large.push_back(data[i1]);
                small.push_back(data[i2]);
            }
        }
        if (leftover)
            tailVal = data.back();

        /* Recursively sort the list of larger elements –
           that becomes our initial “main chain”. */
        C mainChain;
        mainChain.assign(large.begin(), large.end());
        fordJohnsonSort(mainChain);          // recursion

        /* Insert the first pending element: buddy of the
           smallest element in the now-sorted main chain. */
        if (!mainChain.empty())
        {
            const value_type smallestLarge = mainChain.front();
            std::size_t buddyIdx = 0;
            for (; buddyIdx < large.size(); ++buddyIdx)
                if (large[buddyIdx] == smallestLarge)
                    break;

            if (buddyIdx < small.size())
            {
                mainChain.insert(mainChain.begin(), small[buddyIdx]);
                small.erase(small.begin() + buddyIdx);
            }
        }

        /* Merge-insert all remaining pend elements
           (remaining small + optional leftover).            */
        std::vector<value_type> pend;
        pend.reserve(small.size() + (leftover ? 1 : 0));
        pend.insert(pend.end(), small.begin(), small.end());
        if (leftover)
            pend.push_back(tailVal);
        std::sort(pend.begin(), pend.end());          // ascending

        for (std::size_t p = 0; p < pend.size(); ++p)
        {
            typename C::iterator pos =
                std::lower_bound(mainChain.begin(), mainChain.end(), pend[p]);
            mainChain.insert(pos, pend[p]);
        }

        // Copy result back into the user container
        data.assign(mainChain.begin(), mainChain.end());
    }

    // Disable instantiation (this class is purely functional)
    PmergeMe();
    ~PmergeMe();
};

#endif // PMERGEME_HPP
