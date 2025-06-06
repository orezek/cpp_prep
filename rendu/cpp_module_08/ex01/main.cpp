#include "Span.hpp"
#include <iostream>

static void banner(int n, const std::string& what)
{
    std::cout << "\n===== TEST CASE " << n << " -- " << what << " =====\n";
}

int main()
{
    std::cout << "========== SPAN TEST SUITE ==========\n";

    /* 1 — happy-path, 5 ints */
    banner(1, "basic spans (5 numbers)");
    {
        Span sp(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        sp.printNumbers();
        std::cout << "shortestSpan = " << sp.shortestSpan() << '\n';
        std::cout << "longestSpan  = " << sp.longestSpan()  << '\n';
    }

    /* 2 — NotEnoughNumbersException */
    banner(2, "calling spans with < 2 numbers");
    {
        Span sp(3);
        sp.addNumber(42);
        try {
            sp.shortestSpan();
        }
        catch (const std::exception& e) {
            std::cerr << "Caught: " << e.what() << '\n';
        }
    }

    /* 3 — MaxNumbersException via addNumber */
    banner(3, "overflow addNumber()");
    {
        Span sp(2);
        sp.addNumber(1);
        sp.addNumber(2);
        try {
            sp.addNumber(3);           // should throw
        }
        catch (const std::exception& e) {
            std::cerr << "Caught: " << e.what() << '\n';
        }
    }

    /* 4 — addMultipleN fills exactly */
    banner(4, "addMultipleN() fits exactly");
    {
        Span sp(10);
        sp.addNumber(100);
        sp.addNumber(200);
        try {
            sp.addMultipleN(8);        // should fill to 10
            std::cout << "size after fill = 10 ✅\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }

    /* 5 — addMultipleN exceeds capacity */
    banner(5, "addMultipleN() truncated");
    {
        Span sp(6);
        for (int i = 0; i < 4; ++i) sp.addNumber(i);
        sp.addMultipleN(5);            // silent truncation
        sp.printNumbers();
    }

    /* 6 — large random dataset */
    banner(6, "10 000 random numbers");
    {
        const int N = 10000;
        Span sp(N);
        sp.addMultipleN(N);
        std::cout << "shortestSpan = " << sp.shortestSpan() << '\n';
        std::cout << "longestSpan  = " << sp.longestSpan()  << '\n';
    }

    std::cout << "\n========== ALL TESTS COMPLETED ==========\n";
    return 0;
}
