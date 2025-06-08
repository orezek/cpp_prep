#include "RPN.hpp"
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <string>

long RPN::evaluate(const std::string &expr)
{
    if (expr.empty())
        throw std::runtime_error("Empty expression");

    Stack st;
    std::istringstream iss(expr);
    std::string token;

    while (iss >> token)
    {
        /* ---------- single-digit operand ---------- */
        if (token.size() == 1 && std::isdigit(token[0]))
        {
            st.push(token[0] - '0');
        }
        /* ---------- operator token (+ - * /) ---------- */
        else if (token.size() == 1 &&
                 (token[0] == '+' || token[0] == '-' ||
                  token[0] == '*' || token[0] == '/'))
        {
            if (st.size() < 2)
                throw std::runtime_error(
                    std::string("Stack underflow: operator '") + token + "' needs two operands");

            long b = st.top(); st.pop();
            long a = st.top(); st.pop();
            long r = 0;
            char op = token[0];

            switch (op)
            {
                case '+': r = a + b; break;
                case '-': r = a - b; break;
                case '*': r = a * b; break;
                case '/':
                    if (b == 0)
                        throw std::runtime_error("Division by zero");
                    r = a / b;
                    break;
                default:  // should never happen
                    throw std::runtime_error("Unknown operator");
            }
            st.push(r);
        }
        /* ---------- anything else is invalid ---------- */
        else
            throw std::runtime_error("Invalid token: \"" + token + "\"");
    }

    if (st.size() != 1)
        throw std::runtime_error("Too many operands: leftover values after evaluation");

    return st.top();
}

/* suppressed special members (definitions only, no bodies needed) */
RPN::RPN()               {}
RPN::RPN(const RPN &)    {}
RPN &RPN::operator=(const RPN &) { return *this; }
RPN::~RPN()              {}
