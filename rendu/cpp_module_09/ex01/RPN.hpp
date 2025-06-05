#pragma once

#include <stack>
#include <string>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <cctype>

class RPN
{
	public:
		RPN();
		RPN(const RPN&);
		RPN& operator=(const RPN&);
		~RPN();

		void Calculate(const std::string input);

	private:
		void CheckInput(const std::string input);
		void add();
		void subtract();
		void multiply();
		void divide();
		std::stack<long int> stack;
};

