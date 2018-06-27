#pragma once
#include <iostream>
#include <string>
#include <sstream>

class Parser {
public:
	Parser();
	static std::string Parse(std::string expression);
private:
	static bool isoperator(char ch);
	static char process_double_operators(char first, char second);
	static bool check_binary_operator(char op);
};

