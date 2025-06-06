// test_easyfind.cpp
// -------------------------------------------------------------
// C++98 test-suite for easyfind<T>(container, int)
// -------------------------------------------------------------
#include "easyfind.hpp"
#include <vector>
#include <list>
#include <deque>
#include <iostream>

static void printBanner(int n, const std::string& what)
{
    std::cout << "\n===== TEST CASE " << n << " -- " << what << " =====\n";
}

int main()
{
    std::cout << "========== EASYFIND TEST SUITE ==========\n";

    // ---------- 1 : std::vector  (element present) ----------
    printBanner(1, "std::vector<int>  | element present");
    {
        std::vector<int> vec;
        vec.push_back(10); vec.push_back(20); vec.push_back(30);
        try {
            easyfind(vec, 20);
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }

    // ---------- 2 : std::vector  (element absent) ----------
    printBanner(2, "std::vector<int>  | element absent");
    {
        std::vector<int> vec;
        vec.push_back(1); vec.push_back(2); vec.push_back(3);
        try {
            easyfind(vec, 99);          // should throw
        }
        catch (const std::exception& e) {
            std::cerr << "Caught: " << e.what() << '\n';
        }
    }

    // ---------- 3 : std::list    (element present) ----------
    printBanner(3, "std::list<int>    | element present");
    {
        std::list<int> lst;
        lst.push_back(5); lst.push_back(15); lst.push_back(25);
        try {
            easyfind(lst, 25);
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }

    // ---------- 4 : std::list    (element absent) ----------
    printBanner(4, "std::list<int>    | element absent");
    {
        std::list<int> lst;
        lst.push_back(7); lst.push_back(14); lst.push_back(21);
        try {
            easyfind(lst, 0);           // should throw
        }
        catch (const std::exception& e) {
            std::cerr << "Caught: " << e.what() << '\n';
        }
    }

    // ---------- 5 : std::deque   (element present) ----------
    printBanner(5, "std::deque<int>   | element present");
    {
        std::deque<int> deq;
        deq.push_back(42); deq.push_back(43); deq.push_back(44);
        try {
            easyfind(deq, 44);
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }

    // ---------- 6 : std::deque   (element absent) ----------
    printBanner(6, "std::deque<int>   | element absent");
    {
        std::deque<int> deq;
        deq.push_back(-1); deq.push_back(-2); deq.push_back(-3);
        try {
            easyfind(deq, 100);         // should throw
        }
        catch (const std::exception& e) {
            std::cerr << "Caught: " << e.what() << '\n';
        }
    }

    std::cout << "\n========== ALL TESTS COMPLETED ==========\n";
    return 0;
}
