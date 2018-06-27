#pragma once
#include <stack>
#include <string>
#include <sstream>
#include <iostream>
#include <math.h>

class Evaluator {
public:
	//Evaluator();
	//~Evaluator();
	int evaluate(const std::string & expression);
private:
	std::stack<std::string> operator_stack;
	std::stack<int> operand_stack;

	void calculate(int rhs, char op);
	bool higher_precedence(std::string current, std::string top);
	bool is_unary(char op);
	std::string get_matching_parentheses(std::string p);
};

