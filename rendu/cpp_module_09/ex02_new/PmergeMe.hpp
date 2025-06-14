#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <cstddef>      // std::size_t

class PmergeMe
{
public:
    /* Orthodox Canonical Form */
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    /* Public interface */
    static void sort(std::vector<int>& v);
    static void sort(std::deque<int>&  d);

private:
    /* Pair keeps the two partners glued together */
    struct Pair {
        int max;                    // “large” (Aᵢ)
        int min;                    // “small” (Bᵢ)
        Pair() : max(0),  min(0)  {}
        Pair(int big, int small) : max(big), min(small) {}
        bool operator<(const Pair& o) const { return max < o.max; }
    };

    /* Ford-Johnson, concrete overloads */
    static void fordJohnsonSort(std::vector<int>& v);
    static void fordJohnsonSort(std::deque<int>&  d);

    /* Jacobsthal helpers (already implemented in .cpp) */
    static std::size_t jacobsthal(std::size_t k);
    static void makeJacobOrder(std::size_t p, std::vector<std::size_t>& order);
};

#endif /* PMERGEME_HPP */
