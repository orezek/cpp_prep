#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: exactly one quoted RPN expression is required" << std::endl;
        return 1;
    }

    try
    {
        long result = RPN::evaluate(argv[1]);
        std::cout << result << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}



/*
Reverse Polish Notation (RPN) Evaluator in C++98
Introduction to Reverse Polish Notation (RPN)
Reverse Polish Notation (RPN), also known as postfix notation, is a mathematical notation where every operator follows its operands
en.wikipedia.org
. For example, the infix expression (4 + 5) × 6 can be written in RPN as 4 5 + 6 × – notice that the + and × operators come after the numbers. One key advantage is that RPN needs no parentheses as long as each operator has a fixed number of operands
en.wikipedia.org
. This notation was inspired by work of the Polish logician Jan Łukasiewicz in the 1920s, who introduced a parenthesis-free notation (prefix and postfix) for logic expressions
hpmuseum.org
. Hewlett-Packard later coined the term "Reverse Polish Notation" for the postfix variant in honor of Łukasiewicz when they adopted it in their calculators
hpmuseum.org
. In RPN, an expression is evaluated from left to right using a stack (last-in, first-out). As you scan the expression:
Operands (numbers) are pushed onto the stack.
Operators immediately apply to the most recent operands on the stack. This means when an operator is encountered, you pop the required number of values from the stack, apply the operation, and push the result back.

Algo explained in a stack.
---------------------------------------------------------------
For example, consider the RPN expression 3 4 - 5 +:
Push 3, push 4.
Encounter -: pop 4 and 3, compute 3 - 4 = -1, push result -1.
Push 5.
Encounter +: pop 5 and -1, compute -1 + 5 = 4, push result 4.
End of expression: result is the single value 4 on the stack.
---------------------------------------------------------------
Because of this stack-based process, RPN evaluation is linear and unambiguous – there is no need to consider operator precedence or associativity rules at runtime. Each partial result is obtained as soon as its operator is read
hpmuseum.org
. This property made RPN very attractive in early computing and calculator design when memory was limited and CPUs were simple. In fact, computer scientists realized that RPN (postfix) is highly efficient for computation: many compilers and calculators internally convert infix expressions into postfix to evaluate them more easily
hpmuseum.org
. Early computer pioneers also took note – the first computer known to use postfix notation was Konrad Zuse’s Z3 in 1941
en.wikipedia.org
, and later the famed Edsger Dijkstra reintroduced postfix evaluation in the 1960s to minimize memory access using a stack
en.wikipedia.org
.
 */