#pragma once
#include <string>
#include <sstream>
#include "Stack.h"

class Infix_To_Postfix
{
private:
	static const std::string OPERATORS;
	static const std::string SPECIAL_OPERATORS;
	static const int PRECEDENCE[];
	Stack<char> operator_stack;
	std::string postfix;

	void process_operator(char oper);
	bool is_operator(char the_char) const;
	bool is_special_operator(char the_char) const;
	int precedence(char oper) const;
	std::string clean_tokens(std::string expression);
	char check_two_symbol_operator(char one, char two);
	void get_real_operator_symbols(char oper);
	void final_format();

public:
	std::string convert(const std::string& expression);
};

