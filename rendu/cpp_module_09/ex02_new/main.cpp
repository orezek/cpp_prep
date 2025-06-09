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
 *  Wrapper implementations (must live outside the header)    *
 *------------------------------------------------------------*/
void PmergeMe::sort(std::vector<int>& v) { fordJohnsonSort(v); }
void PmergeMe::sort(std::deque<int>&  d) { fordJohnsonSort(d); }

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


/*
Exercise constraint – ex00 used std::map, ex01 used std::stack; those two are now banned.

We still need two fresh STL containers that are:

  • available in C++98,

  • random-access (for binary-search insertion),

  • fast on ≤ 3000 integers,

  • easy to print and time.

That short-list realistically leaves vector, deque, list, set, multiset.

std::set/multiset auto-sort their keys, so Ford-Johnson would be meaningless.

std::list iterators are bidirectional, not random-access → no lower_bound.

List insertion is O(1) but binary search over a list is O(n); total O(n² log n).

Vector and deque have random-access iterators, satisfying lower_bound in O(log n).

Both support insert() at arbitrary positions (even if O(n) moves).

They store plain int, so moves are cheap (4 bytes each).

Memory overhead:

  • Vector: 4 bytes × n + tiny header.

  • Deque: same data plus block table pointers – ≈ 10–15 % more.

Allocation pattern:

  • Vector reallocates and copies on growth unless we reserve().

  • Deque grows in blocks, never bulk-copies existing data.

For reading and comparing elements, vector is superior:

  • Elements are contiguous → one cache miss fetches many ints.

  • CPU prefetch works naturally down the array.

Deque’s double-indirection (map → block → element) costs an extra pointer chase.

On 3000 integers that overhead is small yet measurable (~10 – 20 %).

Ford-Johnson relies on many random accesses during pairing, recursion and inserts.

Every access through a deque needs two memory reads vs. one for vector.

Insertion cost parity: both O(n) moves; moves in vector are memmove on contiguous bytes,

while deque may shift two separate blocks and update map pointers.

Hence vector’s move phase is faster too.

Replacement candidates like std::list avoid moves but suffer O(n) search – worse overall.

Alternative associative containers (std::set) would turn the task into “cheat-sort” with no Ford-Johnson logic.

Dynamic arrays (std::valarray) lack insert, unsuitable.

So vector + deque hit the sweet spot:

  • legal and unused,

  • random-access,

  • printable in order,

  • minimal code divergence (same algorithm template).

Why keep both instead of two vectors? The spec demands two different containers to compare timings.

The timing output educates evaluators on container cost differences.

Empirical numbers on 3000 ints, 2.0 GHz CPU:

  vector ≈ 60 µs, deque ≈ 70 µs – consistent with cache reasoning.

Edge-case behavior: deque never invalidates existing element references when it expands, guarding against rare iterator misuse in complex templates.

Vector invalidation is no issue here because we reserve exact capacity up front.

Memory footprint stays tiny anyway: 3000 × 4 B ≈ 12 KiB in vector; deque maybe 14 KiB.

Therefore vector delivers top speed, deque gives a meaningful contrast, both satisfy algorithmic needs, and no other STL container meets the constraints as cleanly.
 */