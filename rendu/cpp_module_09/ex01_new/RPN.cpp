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

    for (std::string::size_type i = 0; i < expr.size(); ++i) {
        char c = expr[i];

        // 1) skip whitespace
        if (std::isspace(static_cast<unsigned char>(c)))
            continue;

        // 2) digit? push its numeric value
        if (std::isdigit(static_cast<unsigned char>(c))) {
            st.push(c - '0');
        }
        // 3) operator? pop two operands, apply, push result
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (st.size() < 2) {
                std::string msg = "Stack underflow: operator '";
                msg += c;
                msg += "' needs two operands";
                throw std::runtime_error(msg);
            }

            long b = st.top(); st.pop();
            long a = st.top(); st.pop();
            long r = 0;

            switch (c) {
                case '+': r = a + b; break;
                case '-': r = a - b; break;
                case '*': r = a * b; break;
                case '/':
                    if (b == 0)
                        throw std::runtime_error("Division by zero");
                    r = a / b;
                    break;
            }
            st.push(r);
        }
        // 4) anything else is invalid
        else {
            std::string msg = "Invalid character in expression: '";
            msg += c;
            msg += "'";
            throw std::runtime_error(msg);
        }
    }

    // final check: exactly one result must remain
    if (st.size() != 1)
        throw std::runtime_error("Too many operands: leftover values after evaluation");

    return st.top();
}



RPN::RPN()               {}
RPN::RPN(const RPN &)    {}
RPN &RPN::operator=(const RPN &) { return *this; }
RPN::~RPN()              {}
