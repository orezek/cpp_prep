#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>

/*
 * Reverse-Polish-Notation evaluator (static utility class).
 * Throws std::runtime_error with a descriptive message on any malformed input.
 */
class RPN
{
public:
    static long evaluate(const std::string &expression);

private:                // no instances or copies (pure utility)
    typedef std::stack<long> Stack;

    RPN();
    RPN(const RPN &);
    RPN &operator=(const RPN &);
    ~RPN();
};

#endif // RPN_HPP
