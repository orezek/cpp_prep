#pragma once
#include <iostream>
#include <string>

class StringUtils
{
	private:
		StringUtils();
		StringUtils(const StringUtils&);
		const StringUtils& operator=(const StringUtils&);
		~StringUtils();

	public:
		static bool isDigitAndDot(const std::string str);
};
