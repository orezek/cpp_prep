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
#include <utility> // std::pair

#include <iostream>

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
        typedef std::pair<value_type, value_type> Pair;
        const std::size_t n = data.size();
        if (n < 2) return;

        /* ---- 1. Create Pairs & Handle Straggler ------------------------ */
        bool hasStraggler = (n % 2) != 0;
        value_type straggler = hasStraggler ? data.back() : value_type();
        std::vector<Pair> pairs;
        pairs.reserve(n / 2);
        for (std::size_t i = 0; i < n / 2; ++i) {
            value_type& a = data[2 * i];
            value_type& b = data[2 * i + 1];
            if (a < b)  pairs.push_back(std::make_pair(b, a));
            else        pairs.push_back(std::make_pair(a, b));
        }


        // Lets start dancing: we must do the "extract -> recurse -> remap" dance
        /* ---- 2. Recursively Sort Pairs by the "large" Element ---------- */
        std::vector<value_type> largeElements;
        largeElements.reserve(pairs.size());
        for (typename std::vector<Pair>::iterator it = pairs.begin(); it != pairs.end(); ++it) {
            largeElements.push_back(it->first);
        }
        fordJohnsonSort(largeElements);
        std::vector<Pair> sortedPairs;
        sortedPairs.reserve(pairs.size());
        // reconstruction loop .
        for (size_t i = 0; i < largeElements.size(); ++i) {
            for (size_t j = 0; j < pairs.size(); ++j) {
                if (pairs[j].first == largeElements[i]) {
                    sortedPairs.push_back(pairs[j]);
                    pairs.erase(pairs.begin() + j); // Erase to handle duplicates correctly
                    break;
                }
            }
        }
        // End od dancing sequence


        /* ---- 3. Create Main Chain and Pend Elements -------------------- */
        C mainChain;
        std::vector<value_type> pend;
        mainChain.assign(largeElements.begin(), largeElements.end());
        pend.reserve(sortedPairs.size());
        for (size_t i = 0; i < sortedPairs.size(); ++i) {
            pend.push_back(sortedPairs[i].second);
        }

        /* ---- 4. Insert First Pend Element ------------------------------- */
        mainChain.insert(mainChain.begin(), pend[0]);

        /* ---- 5. Generate Jacobsthal Insertion Schedule ----------------- */
        std::vector<std::size_t> schedule;
        makeJacobOrder(pend.size() - 1, schedule);

        /* ---- 6. Insert Remaining Pend Elements (Optimized Search) ------ */
        for (std::size_t s = 0; s < schedule.size(); ++s)
        {
            // Get the value 'b_i' to insert from the pend list using the Jacobsthal schedule.
            // The schedule is 0-indexed for the remaining pend elements (pend[1], pend[2], ...).
            std::size_t pend_idx = schedule[s] + 1;
            const value_type val_b = pend[pend_idx];
            // Get its partner 'a_i'. The pairs are already sorted by 'a_i'.
            const value_type val_a = sortedPairs[pend_idx].first;

            // Find the position of 'a_i' in the mainChain. This is our search limit.
            // We can use lower_bound because mainChain is sorted.
            typename C::iterator search_limit =
                std::lower_bound(mainChain.begin(), mainChain.end(), val_a);

            // Find the insertion point for 'b_i' using a binary search
            // ONLY in the range from the beginning to its partner's position.
            typename C::iterator pos =
                std::lower_bound(mainChain.begin(), search_limit, val_b);

            mainChain.insert(pos, val_b);
        }

        /* ---- 7. Insert the Straggler (if it exists) -------------------- */
        if (hasStraggler) {
            typename C::iterator pos =
                std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
            mainChain.insert(pos, straggler);
        }

        /* ---- 8. Copy Result Back Out ----------------------------------- */
        data.assign(mainChain.begin(), mainChain.end());
    }
};

#endif /* PMERGEME_HPP */