#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& refObj) { *this = refObj; }

RPN& RPN::operator=(const RPN& refObj) { (void) refObj; return(*this); }

RPN::~RPN() {}

void RPN::CheckInput(const std::string input)
{
	for (size_t i = 0; i < input.length(); ++i)
	{
		char c = input[i];
		if (!isdigit(c) && c != '+' && c != '-' && c != '*' && c != '/' && c != ' ')
		{
			throw std::invalid_argument("Invalid characters in input.");
		}
	}
}

void RPN::add()
{
	int a;
	int b;

	if (stack.size() < 2)
		throw std::invalid_argument("Invalid input.");

	a = stack.top();
	stack.pop();
	b = stack.top();
	stack.pop();

	stack.push(b + a);
}

void RPN::subtract()
{
	int a;
	int b;

	if (stack.size() < 2)
		throw std::invalid_argument("Invalid input.");

	a = stack.top();
	stack.pop();
	b = stack.top();
	stack.pop();

	stack.push(b - a);
}

void RPN::multiply()
{
	int a;
	int b;

	if (stack.size() < 2)
		throw std::invalid_argument("Invalid input.");

	a = stack.top();
	stack.pop();
	b = stack.top();
	stack.pop();

	stack.push(b * a);
}

void RPN::divide()
{
	int a;
	int b;

	if (stack.size() < 2)
		throw std::invalid_argument("Invalid input.");
	if (stack.top() == 0)
		throw std::domain_error("Cannot divide by 0.");

	a = stack.top();
	stack.pop();		
	b = stack.top();
	stack.pop();

	stack.push(b / a);
}

void RPN::Calculate(const std::string input)
{
	CheckInput(input);

	std::string::const_iterator it;
	for (it = input.begin(); it != input.end(); ++it)
	{
		char c = *it;

		if (isspace(c))
			continue ;
		if (isdigit(c)) 
		{
			stack.push(c - '0');
			continue;
		}
		else
		{
			switch (c)
			{
				case '+':
					add();
					break;
				case '-':
					subtract();
					break;
				case '*':
					multiply();
					break;
				case '/':
					divide();
					break;
				default:
					throw std::invalid_argument("Invalid input.");
			}
		}
	}
	if (stack.size() != 1)
		throw std::invalid_argument("Invalid input.");
	std::cout << stack.top() << std::endl;
}