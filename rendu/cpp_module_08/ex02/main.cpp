// test_mutantstack.cpp
// -------------------------------------------------------------
// C++98 test-suite for MutantStack (now 10 cases)
// -------------------------------------------------------------
#include "MutantStack.hpp"
#include <iostream>
#include <string>
#include <vector>   // needed for case 9

static void banner(int n, const std::string& what)
{
    std::cout << "\n===== TEST CASE " << n << " -- " << what << " =====\n";
}

int main()
{
    std::cout << "========== MUTANTSTACK TEST SUITE ==========\n";

    /* 1 — basic stack operations */
    banner(1, "push / pop / size / top");
    {
        MutantStack<int> ms;
        ms.push(5);
        ms.push(17);
        std::cout << "top      = " << ms.top()  << '\n';
        ms.pop();
        std::cout << "size     = " << ms.size() << '\n';
        ms.push(3);
        ms.push(42);
        std::cout << "new size = " << ms.size() << '\n';
    }

    /* 2 — forward iteration with iterator */
    banner(2, "iterator traversal");
    {
        MutantStack<int> ms;
        for (int i = 0; i < 5; ++i) ms.push(i * 10);
        for (MutantStack<int>::iterator it = ms.begin(); it != ms.end(); ++it)
            std::cout << *it << ' ';
        std::cout << '\n';
    }

    /* 3 — forward traversal with const_iterator */
    banner(3, "const_iterator traversal");
    {
        MutantStack<int> ms;
        ms.push(1); ms.push(2); ms.push(3);
        const MutantStack<int>& ref = ms;
        for (MutantStack<int>::const_iterator it = ref.begin(); it != ref.end(); ++it)
            std::cout << *it << ' ';
        std::cout << '\n';
    }

    /* 4 — reverse iteration and in-place modification via iterator */
    banner(4, "reverse_iterator & modification");
    {
        MutantStack<int> ms;
        for (int i = 1; i <= 4; ++i) ms.push(i);
        for (MutantStack<int>::iterator it = ms.begin(); it != ms.end(); ++it)
            *it *= 2;                               // modify
        for (MutantStack<int>::reverse_iterator rit = ms.rbegin();
             rit != ms.rend(); ++rit)
            std::cout << *rit << ' ';
        std::cout << '\n';
    }

    /* 5 — copy-construct into std::stack */
    banner(5, "copy-construct std::stack from MutantStack");
    {
        MutantStack<std::string> ms;
        ms.push("alpha");
        ms.push("beta");
        std::stack<std::string> plain(ms);          // must compile
        std::cout << "plain.top() = " << plain.top() << '\n';
    }

    /* 6 — assignment operator */
    banner(6, "assignment operator");
    {
        MutantStack<int> a; a.push(10); a.push(20);
        MutantStack<int> b; b.push(1); b.push(2); b.push(3);
        a = b;
        std::cout << "size after assignment = " << a.size() << '\n';
        for (MutantStack<int>::iterator it = a.begin(); it != a.end(); ++it)
            std::cout << *it << ' ';
        std::cout << '\n';
    }

    /* 7 — copy constructor independence */
    banner(7, "copy constructor, independence check");
    {
        MutantStack<int> orig;
        orig.push(7); orig.push(8); orig.push(9);

        MutantStack<int> copy(orig);   // invoke copy-ctor
        copy.push(99);                 // mutate the copy

        std::cout << "orig size = " << orig.size()
                  << ", copy size = " << copy.size() << '\n';

        std::cout << "orig top = " << orig.top()
                  << ", copy top = " << copy.top() << '\n';
    }

    /* 8 — const reverse iteration */
    banner(8, "const_reverse_iterator traversal");
    {
        MutantStack<int> ms;
        for (int i = 0; i < 4; ++i) ms.push(i + 1);
        const MutantStack<int>& cref = ms;
        for (MutantStack<int>::const_reverse_iterator rit = cref.rbegin();
             rit != cref.rend(); ++rit)
            std::cout << *rit << ' ';
        std::cout << '\n';
    }

    /* 9 — MutantStack with std::vector as underlying container */
    banner(9, "MutantStack<int, vector<int>>");
    {
        MutantStack<int, std::vector<int> > vstack;
        vstack.push(100); vstack.push(200); vstack.push(300);
        for (MutantStack<int, std::vector<int> >::iterator it = vstack.begin();
             it != vstack.end(); ++it)
            std::cout << *it << ' ';
        std::cout << "\n(top = " << vstack.top() << ")\n";
    }

    /* 10 — push / pop stress test (1000 ops) */
    banner(10, "stress push / pop loop");
    {
        MutantStack<int> ms;

        for (int i = 0; i < 500; ++i) ms.push(i);
        for (int i = 0; i < 250; ++i) ms.pop();
        for (int i = 500; i < 1000; ++i) ms.push(i);

        std::cout << "size = " << ms.size()
                  << ", top = " << ms.top() << '\n';

        std::cout << "first five elements: ";
        int printed = 0;
        for (MutantStack<int>::iterator it = ms.begin();
             it != ms.end() && printed < 5; ++it, ++printed)
            std::cout << *it << ' ';
        std::cout << '\n';
    }

    std::cout << "\n========== ALL TESTS COMPLETED ==========\n";
    return 0;
}
